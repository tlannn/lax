#include "vm/VM.h"
#include "compiler/Compiler.h"
#include "natives/NativeFunctions.h"
#include "objects/ObjClosure.h"
#include "objects/ObjFunction.h"
#include "objects/ObjUpvalue.h"
#include "utils/Logger.h"

/// Class constructor.
VM::VM() : _frameCount(0), _openUpvalues(nullptr), _frames{} {
	_stackTop = _stack;

	// Register native functions
	defineNative("print", printNative);
}

/// Compile an Abstract Syntax Tree to bytecode and then run the bytecode
/// generated.
InterpretResult VM::interpret(ASTNode *ast) {
	// Compile the AST to bytecode
	Compiler compiler;
	ObjFunction *function = compiler.compile(ast);

	// Stop there if errors occurred during compilation
	if (function == nullptr) return INTERPRET_COMPILE_ERROR;

	// Wrap the function in a closure and push it onto the stack
	auto *closure = new ObjClosure(function);
	push(OBJ_VAL(closure));
	call(closure, 0);

	// Execute the bytecode
	return run();
}

/// Execute the bytecode.
InterpretResult VM::run() {
	CallFrame *frame = &_frames[_frameCount - 1];

#define READ_BYTE()			(*frame->ip++)
#define READ_SHORT()		(static_cast<uint16_t>((READ_BYTE() << 8) | READ_BYTE()))
#define READ_CONSTANT()		(frame->closure->getFunction()->getChunk()->getConstant(extendedArg | READ_BYTE()))
#define READ_STRING()    	(AS_STRING(READ_CONSTANT()))
#define BINARY_OP(valueType, op) \
    do { \
      if (!IS_INT(peek(0)) || !IS_INT(peek(1))) { \
        runtimeError("Operands must be numbers"); \
        return INTERPRET_RUNTIME_ERROR; \
      } \
	  Value b = pop(); \
      Value a = pop(); \
      push(valueType(AS_INT(a) op AS_INT(b))); \
    } while (false)
// End of BINARY_OP macro

	uint16_t extendedArg = 0;

	for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
		std::cout << "Stack trace: ";
		for (Value *slot = _stack; slot < _stackTop; ++slot) {
			std::cout << "[ " << Value::toString(*slot) << " ]";
		}
		std::cout << std::endl;

		disassembleInstruction(frame->closure->getFunction()->getChunk(),
							   (int)(frame->ip - frame->closure->getFunction()->getChunk()->getCode()));
		std::cout << std::endl;
#endif

		// Read the next OpCode
		uint8_t instruction = READ_BYTE();

		// Execute the instruction
		switch (instruction) {
			case OP_EXTENDED_ARG:	extendedArg = extendedArg == 0 ? 1 << 8 : extendedArg << 8;
			case OP_CONSTANT: {
				Value constant = READ_CONSTANT();
				extendedArg = 0;

				push(constant);
				break;
			}
			case OP_NULL: 			push(NULL_VAL); break;
			case OP_TRUE: 			push(BOOL_VAL(true)); break;
			case OP_FALSE: 			push(BOOL_VAL(false)); break;
			case OP_POP:			pop(); break;
			case OP_DEFINE_GLOBAL: {
				ObjString *name = READ_STRING();
				_globals.set(name, peek(0));
				pop();
				break;
			}
			case OP_GET_GLOBAL: {
				ObjString *name = READ_STRING();
				Value value;

				// Check if global variable exists
				if (!_globals.get(name, &value)) {
					runtimeError("Undefined variable " + name->toString());
					return INTERPRET_RUNTIME_ERROR;
				}

				push(value);
				break;
			}
			case OP_SET_GLOBAL: {
				ObjString *name = READ_STRING();

				// Check if global variable exists
				if (_globals.set(name, peek(0))) {
					_globals.remove(name);

					runtimeError("Undefined variable " + name->toString());
					return INTERPRET_RUNTIME_ERROR;
				}
				break;
			}
			case OP_GET_UPVALUE: {
				uint8_t slot = READ_BYTE();

				// Dereference the pointer to the location where the captured value is stored
				// and push that value into the stack
				push(*frame->closure->getUpvalues()[slot]->getLocation());
				break;
			}
			case OP_SET_UPVALUE: {
				uint8_t slot = READ_BYTE();

				// Dereference the pointer to the location where the captured value is stored
				// and change that value
				*frame->closure->getUpvalues()[slot]->getLocation() = peek(0);
				break;
			}
			case OP_GET_LOCAL: {
				uint8_t slot = READ_BYTE();
				push(frame->slots[slot]);
				break;
			}
			case OP_SET_LOCAL: {
				uint8_t slot = READ_BYTE();
				frame->slots[slot] = peek(0);
				break;
			}
			case OP_EQUAL: {
				Value b = pop();
				Value a = pop();
				push(BOOL_VAL(Value::equals(a, b)));
				break;
			}
			case OP_NOT_EQUAL:{
				Value b = pop();
				Value a = pop();
				push(BOOL_VAL(!Value::equals(a, b)));
				break;
			}
			case OP_LESS:			BINARY_OP(BOOL_VAL, <); break;
			case OP_LESS_EQUAL:		BINARY_OP(BOOL_VAL, <=); break;
			case OP_GREATER:		BINARY_OP(BOOL_VAL, >); break;
			case OP_GREATER_EQUAL:	BINARY_OP(BOOL_VAL, >=); break;
			case OP_ADD:			BINARY_OP(INT_VAL, +); break;
			case OP_SUBTRACT:		BINARY_OP(INT_VAL, -); break;
			case OP_MULTIPLY:		BINARY_OP(INT_VAL, *); break;
			case OP_DIVIDE:			BINARY_OP(INT_VAL, /); break;
			case OP_NOT:			push(BOOL_VAL(Value::isFalsy(pop()))); break;
			case OP_NEGATE: {
				// Only numbers can be negated
				if (!IS_INT(peek(0))) {
					runtimeError("Operand must be a number");
					return INTERPRET_RUNTIME_ERROR;
				}

				push(INT_VAL(-AS_INT(pop())));
				break;
			}
			case OP_CALL: {
				int argCount = READ_BYTE();

				// Check that the call successfully occurred
				if (!callValue(peek(argCount), argCount))
					return INTERPRET_RUNTIME_ERROR;

				// Go back to the previous call frame
				frame = &_frames[_frameCount - 1];
				break;
			}
			case OP_CLOSURE: {
				// Create a closure out of the function and push it into the stack
				ObjFunction *function = AS_FUNCTION(READ_CONSTANT());
				auto *closure = new ObjClosure(function);
				push(OBJ_VAL(closure));

				// Save all upvalues in the closure
				for (int i = 0; i < closure->getUpvalueCount(); ++i) {
					uint8_t isLocal = READ_BYTE();
					uint8_t index = READ_BYTE();
					if (isLocal)
						closure->getUpvalues()[i] = captureUpvalue(frame->slots + index);
					else
						closure->getUpvalues()[i] = frame->closure->getUpvalues()[index];
				}
				break;
			}
			case OP_CLOSE_UPVALUE: {
				closeUpvalues(_stackTop - 1);
				pop();
				break;
			}
			case OP_JUMP: {
				auto offset = READ_SHORT();
				frame->ip += offset;
				break;
			}
			case OP_JUMP_FALSE: {
				auto offset = READ_SHORT();
				if (Value::isFalsy(peek(0)))
					frame->ip += offset;
				break;
			}
			case OP_LOOP: {
				uint16_t offset = READ_SHORT();
				frame->ip -= offset;
				break;
			}
			case OP_RETURN: {
				Value result = pop();
				closeUpvalues(frame->slots);
				_frameCount--;

				// Exit the code if the return instruction occurred at top-level
				//
				// Note that the return instruction is not equivalent to a return statement at top-level
				// It is automatically generated by the compiler at the end of the bytecode to inform
				// that the end of the source code is reached
				if (_frameCount == 0) {
					pop();
					return INTERPRET_OK;
				}

				// Update the stack so its top value refers to the last value in the stack at the time of the
				// previous frame
				_stackTop = frame->slots;
				push(result);

				// Go back to the previous call frame if the return instruction occurred within a function
				frame = &_frames[_frameCount - 1];
				break;
			}
			default:
				runtimeError("Unknown opcode " + std::to_string(instruction));
				break;
		}
	}

#undef READ_BYTE
#undef READ_SHORT
#undef READ_CONSTANT
#undef READ_STRING
#undef BINARY_OP

	return INTERPRET_RUNTIME_ERROR; // Unreachable
}

/// Report an error.
void VM::runtimeError(const std::string &message) {
	Logger::error(message);
}

/// Push a value onto the runtime stack.
void VM::push(Value value) {
	*_stackTop = value;
	++_stackTop;
}

/// Pop the topmost value of the runtime stack.
Value VM::pop() {
	--_stackTop;
	return *_stackTop;
}

/// Peek a value at some distance in the runtime stack.
Value VM::peek(int distance) {
	return _stackTop[-1 - distance];
}

/// Create an upvalue for a value in the stack, if it doesn't already exist.
///
/// The upvalue created is added to the list of opened upvalues, ordered by
/// stack index.
ObjUpvalue* VM::captureUpvalue(Value *local) {
	ObjUpvalue *previous = nullptr;
	ObjUpvalue *upvalue = _openUpvalues;

	// Look for an existing upvalue for the local variable
	while (upvalue != nullptr && upvalue->getLocation() > local) {
		previous = upvalue;
		upvalue = upvalue->getNext();
	}

	// Return that upvalue if it exists
	if (upvalue != nullptr && upvalue->getLocation() == local)
		return upvalue;

	// Create a new upvalue and add it to the list of opened upvalues
	auto *createdUpvalue = new ObjUpvalue(local);
	createdUpvalue->setNext(upvalue);

	if (previous == nullptr)
		_openUpvalues = createdUpvalue;
	else
		previous->setNext(createdUpvalue);

	return createdUpvalue;
}

/// Close upvalues in the list of opened upvalues that are above a value in
/// the stack.
///
/// When leaving a scope, all upvalues used in that scope are closed. Closed
/// upvalues are moved off the stack and saved in the upvalue object itself,
/// so the value can still be accessed outside of its scope.
void VM::closeUpvalues(Value *last) {
	// Close upvalues whose index are greater than the index of the value referenced in the stack
	// Opened upvalues are ordered by stack index
	while (_openUpvalues != nullptr && _openUpvalues->getLocation() >= last) {
		ObjUpvalue *upvalue = _openUpvalues;
		upvalue->setClosed(*upvalue->getLocation()); // Move the value off the stack into the upvalue object
		_openUpvalues = upvalue->getNext();
	}
}

/// Perform a call on a value.
bool VM::callValue(Value callee, int argCount) {
	// Only some objects are callable
	if (IS_OBJ(callee)) {
		switch (OBJ_TYPE(callee)) {
			case OBJ_CLOSURE: 	return call(AS_CLOSURE(callee), argCount);
			case OBJ_NATIVE: {
				NativeFn native = AS_NATIVE(callee);
				Value result = native(argCount, _stackTop - argCount); // Execute the native function

				// Push the function result on top of the stack
				_stackTop -= argCount + 1;
				push(result);
				return true;
			}
			default: break;
		}
	}

	runtimeError("Can only call functions and classes");
	return false;
}

/// Call a function and execute its body.
bool VM::call(ObjClosure *closure, int argCount) {
	ObjFunction *function = closure->getFunction();

	// Check that the correct number of arguments has been passed to the call
	if (argCount != function->arity()) {
		runtimeError("Expected " + std::to_string(function->arity()) + " parameters but got " +
						std::to_string(argCount));
		return false;
	}

	// Check that the maximum number of call frames isn't reached
	if (_frameCount == FRAMES_MAX) {
		runtimeError("Stack overflow");
		return false;
	}

	// Create a new call frame for the function
	CallFrame &frame = _frames[_frameCount++];
	frame.closure = closure;
	frame.ip = function->getChunk()->getCode();
	frame.slots = _stackTop - argCount - 1; // Narrow the stack window for the function

	return true;
}

/// Register a native function in the global scope.
void VM::defineNative(const char *name, NativeFn function) {
	push(OBJ_VAL(ObjString::copyString(name)));
	push(OBJ_VAL(new ObjNative(function)));
	_globals.set(AS_STRING(_stack[0]), _stack[1]);
	pop();
	pop();
}

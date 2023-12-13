#include "vm/VM.h"
#include "compiler/Compiler.h"
#include "natives/NativeFunctions.h"
#include "objects/ObjClosure.h"
#include "objects/ObjFunction.h"
#include "objects/ObjUpvalue.h"
#include "utils/Logger.h"

VM::VM() :
    m_frameCount(0),
    m_openUpvalues(nullptr),
    m_frames{},
    m_stackTop(m_stack)
{
    // Register native functions
    defineNative("print", printNative);
}

InterpretResult VM::interpret(AST& ast) {
    // Compile the AST to bytecode
    Compiler compiler;
    ObjFunction* function = compiler.compile(ast);

    // Stop there if errors occurred during compilation
    if (function == nullptr) return INTERPRET_COMPILE_ERROR;

    // Wrap the function in a closure and push it onto the stack
    auto* closure = new ObjClosure(function);
    push(Value::object(closure));
    call(closure, 0);

    // Execute the bytecode
    return run();
}

InterpretResult VM::run() {
    CallFrame* frame = &m_frames[m_frameCount - 1];

#define CHUNK()             (frame->closure->getFunction()->getChunk())
#define READ_BYTE()         (*frame->ip++)
#define READ_SHORT()        ((uint16_t)((READ_BYTE() << 8) | READ_BYTE()))
#define READ_CONSTANT()     (CHUNK()->getConstant(extendedArg | READ_BYTE()))
#define READ_STRING()       (AS_STRING(READ_CONSTANT()))
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
        for (Value *slot = m_stack; slot < m_stackTop; ++slot) {
            std::cout << "[ " << Value::toString(*slot) << " ]";
        }
        std::cout << std::endl;

        disassembleInstruction(CHUNK(),
                               (int)(frame->ip - CHUNK()->getCode()));
        std::cout << std::endl;
#endif

        // Read the next OpCode
        uint8_t instruction = READ_BYTE();

        // Execute the instruction
        switch (instruction) {
            case OP_EXTENDED_ARG:
                extendedArg = extendedArg == 0 ? 1 << 8 : extendedArg << 8;
                break;
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                extendedArg = 0;

                push(constant);
                break;
            }
            case OP_NULL:
                push(Value::null());
                break;
            case OP_TRUE:
                push(Value::boolean(true));
                break;
            case OP_FALSE:
                push(Value::boolean(false));
                break;
            case OP_POP:
                pop();
                break;
            case OP_DEFINE_GLOBAL: {
                ObjString* name = READ_STRING();
                m_globals.set(name, peek(0));
                pop();
                break;
            }
            case OP_GET_GLOBAL: {
                ObjString* name = READ_STRING();
                Value value;

                // Check if global variable exists
                if (!m_globals.get(name, &value)) {
                    runtimeError("Undefined variable " + name->toString());
                    return INTERPRET_RUNTIME_ERROR;
                }

                push(value);
                break;
            }
            case OP_SET_GLOBAL: {
                ObjString* name = READ_STRING();

                // Check if global variable exists
                if (m_globals.set(name, peek(0))) {
                    m_globals.remove(name);

                    runtimeError("Undefined variable " + name->toString());
                    return INTERPRET_RUNTIME_ERROR;
                }
                break;
            }
            case OP_GET_UPVALUE: {
                uint8_t slot = READ_BYTE();

                // Dereference the pointer to the location where the captured
                // value is stored and push that value into the stack
                push(*frame->closure->getUpvalues()[slot]->getLocation());
                break;
            }
            case OP_SET_UPVALUE: {
                uint8_t slot = READ_BYTE();

                // Dereference the pointer to the location where the captured
                // value is stored and change that value
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
                push(Value::boolean(Value::equals(a, b)));
                break;
            }
            case OP_NOT_EQUAL: {
                Value b = pop();
                Value a = pop();
                push(Value::boolean(!Value::equals(a, b)));
                break;
            }
            case OP_LESS:           BINARY_OP(Value::boolean, <);
                break;
            case OP_LESS_EQUAL:     BINARY_OP(Value::boolean, <=);
                break;
            case OP_GREATER:        BINARY_OP(Value::boolean, >);
                break;
            case OP_GREATER_EQUAL:  BINARY_OP(Value::boolean, >=);
                break;
            case OP_ADD:            BINARY_OP(Value::integer, +);
                break;
            case OP_SUBTRACT:       BINARY_OP(Value::integer, -);
                break;
            case OP_MULTIPLY:       BINARY_OP(Value::integer, *);
                break;
            case OP_DIVIDE:         BINARY_OP(Value::integer, /);
                break;
            case OP_NOT:
                push(Value::boolean(Value::isFalsy(pop())));
                break;
            case OP_NEGATE: {
                // Only numbers can be negated
                if (!IS_INT(peek(0))) {
                    runtimeError("Operand must be a number");
                    return INTERPRET_RUNTIME_ERROR;
                }

                push(Value::integer(-AS_INT(pop())));
                break;
            }
            case OP_CALL: {
                int argCount = READ_BYTE();

                // Check that the call successfully occurred
                if (!callValue(peek(argCount), argCount))
                    return INTERPRET_RUNTIME_ERROR;

                // Go back to the previous call frame
                frame = &m_frames[m_frameCount - 1];
                break;
            }
            case OP_CLOSURE: {
                // Create a closure out of the function and push it into the stack
                ObjFunction* function = AS_FUNCTION(READ_CONSTANT());
                auto* closure = new ObjClosure(function);
                push(Value::object(closure));

                // Save all upvalues in the closure
                for (int i = 0; i < closure->getUpvalueCount(); ++i) {
                    uint8_t isLocal = READ_BYTE();
                    uint8_t index = READ_BYTE();
                    closure->getUpvalues()[i] = isLocal
                        ? captureUpvalue(frame->slots + index)
                        : frame->closure->getUpvalues()[index];
                }
                break;
            }
            case OP_CLOSE_UPVALUE: {
                closeUpvalues(m_stackTop - 1);
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
            case OP_RETURN: {
                Value result = pop();
                closeUpvalues(frame->slots);
                m_frameCount--;

                // Exit the code if the return instruction occurred at top-level
                //
                // Note that the return instruction is not equivalent to a
                // return statement at top-level. It is automatically generated
                // by the compiler at the end of the bytecode to inform that the
                // end of the source code is reached
                if (m_frameCount == 0) {
                    pop();
                    return INTERPRET_OK;
                }

                // Update the stack so its top value refers to the last value
                // in the stack at the time of the previous frame
                m_stackTop = frame->slots;
                push(result);

                // Go back to the previous call frame if the return instruction
                // occurred within a function
                frame = &m_frames[m_frameCount - 1];
                break;
            }
            default:
                runtimeError("Unknown opcode " + std::to_string(instruction));
                break;
        }
    }

#undef CHUNK
#undef READ_BYTE
#undef READ_SHORT
#undef READ_CONSTANT
#undef READ_STRING
#undef BINARY_OP

    return INTERPRET_RUNTIME_ERROR; // Unreachable
}

void VM::runtimeError(const std::string& message) {
    Logger::error(message);
}

void VM::push(Value value) {
    *m_stackTop = value;
    ++m_stackTop;
}

Value VM::pop() {
    --m_stackTop;
    return *m_stackTop;
}

Value VM::peek(int distance) {
    if (m_stackTop - m_stack <= distance)
        throw std::out_of_range("Stack underflow");

    return *(m_stackTop - distance - 1);
}

ObjUpvalue* VM::captureUpvalue(Value* local) {
    ObjUpvalue* previous = nullptr;
    ObjUpvalue* upvalue = m_openUpvalues;

    // Look for an existing upvalue for the local variable
    while (upvalue != nullptr && upvalue->getLocation() > local) {
        previous = upvalue;
        upvalue = upvalue->getNext();
    }

    // Return that upvalue if it exists
    if (upvalue != nullptr && upvalue->getLocation() == local)
        return upvalue;

    // Create a new upvalue and add it to the list of opened upvalues
    auto* createdUpvalue = new ObjUpvalue(local);
    createdUpvalue->setNext(upvalue);

    if (previous == nullptr)
        m_openUpvalues = createdUpvalue;
    else
        previous->setNext(createdUpvalue);

    return createdUpvalue;
}

void VM::closeUpvalues(Value* last) {
    // Close upvalues whose index are greater than the index of the value
    // referenced in the stack
    // Opened upvalues are ordered by stack index
    while (m_openUpvalues != nullptr && m_openUpvalues->getLocation() >= last) {
        ObjUpvalue* upvalue = m_openUpvalues;

        // Move the value off the stack into the upvalue object
        upvalue->setClosed(*upvalue->getLocation());
        m_openUpvalues = upvalue->getNext();
    }
}

bool VM::callValue(Value callee, int argCount) {
    // Only some objects are callable
    if (IS_OBJ(callee)) {
        switch (OBJ_TYPE(callee)) {
            case OBJ_CLOSURE:
                return call(AS_CLOSURE(callee), argCount);
            case OBJ_NATIVE: {
                NativeFn native = AS_NATIVE(callee);

                // Execute the native function
                Value result = native(argCount, m_stackTop - argCount);

                // Push the function result on top of the stack
                m_stackTop -= argCount + 1;
                push(result);
                return true;
            }
            default:
                break;
        }
    }

    runtimeError("Can only call functions and classes");
    return false;
}

bool VM::call(ObjClosure* closure, int argCount) {
    ObjFunction* function = closure->getFunction();

    // Check that the correct number of arguments has been passed to the call
    if (argCount != function->arity()) {
        runtimeError(
            "Expected " + std::to_string(function->arity()) +
            " parameters but got " + std::to_string(argCount));
        return false;
    }

    // Check that the maximum number of call frames isn't reached
    if (m_frameCount == FRAMES_MAX) {
        runtimeError("Stack overflow");
        return false;
    }

    // Create a new call frame for the function
    CallFrame& frame = m_frames[m_frameCount++];
    frame.closure = closure;
    frame.ip = function->getChunk()->getCode();
    frame.slots = m_stackTop - argCount - 1; // Narrow the stack window for
    // the function

    return true;
}

void VM::defineNative(const char* name, NativeFn function) {
    push(Value::object(ObjString::copyString(name)));
    push(Value::object(new ObjNative(function)));
    m_globals.set(AS_STRING(m_stack[0]), m_stack[1]);
    pop();
    pop();
}

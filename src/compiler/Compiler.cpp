#include "compiler/Compiler.h"
#include "common/Chunk.h"
#include "objects/ObjFunction.h"
#include "objects/ObjString.h"
#include "objects/Variable.h"
#include "utils/Logger.h"

/// Class constructor.
Compiler::Compiler() : _currentScope(nullptr), _errors(false) {}

/// Compile an AST to bytecode.
ObjFunction* Compiler::compile(AST &ast) {
	// Create a scope for the top-level
	Scope scope;
	initScope(&scope, TYPE_SCRIPT);

	// Compile the abstract syntax tree to bytecode
	ast.traverse(*this);

	// End compilation
	ObjFunction *script = endCurrentScope();

	return _errors ? nullptr : script;
}

bool Compiler::writeBytecode(Chunk *chunk) {
	Logger::warning("bytecode output");
	std::ofstream file("output.clax", std::ios::out | std::ios::binary);

	uint16_t constantCount = chunk->getConstantCount();

	if (!file.is_open())
		return false;

	Logger::log("step1");

	std::cout << (constantCount == 10 ? "true" : "false") << std::endl;

	// Write the number of items in constant pool
	uint8_t bytes[] = {static_cast<uint8_t>(constantCount >> 8), static_cast<uint8_t>(constantCount & 0xff)};
	const char *count = (char*)&bytes;
	std::cout << std::to_string(bytes[0]) << std::endl;
	std::cout << std::to_string(bytes[1]) << std::endl;

	file.write(count, 2);
//	file.write(reinterpret_cast<const char *>(bytes[0]), 1);
//	file.write(reinterpret_cast<const char *>(bytes[1]), 1);

	Logger::log("step2");

	// Write constant pool
	for (int offset = 0; offset < constantCount; ++offset) {
		Value constant = chunk->getConstant(offset);

//		file.write(reinterpret_cast<const char *>(&constant), sizeof(Value));

		char *p_constant = (char*)&constant;

		for (int i = 0; i < sizeof(Value); ++i) {
			file.write(p_constant + i, 1);
		}


//		if (IS_STRING(constant)) {
//			ObjString *string = AS_STRING(constant);
//			file.write(string->getChars(), string->getLength());
//		}
	}

	Logger::log("step3");

	// Write instructions
	for (int offset = 0; offset < chunk->getCount(); ++offset) {
		uint8_t *byte = chunk->getCode(offset);
		file.write((char*)byte, 1);

//		if (*byte == OP_RETURN)
//			break;
	}

	Logger::log("step4");

	file.close();

	return file.good();
}

/// Report an error.
void Compiler::error(const std::string &message) {
	_errors = true;
	Logger::error(message);
}

/// Return the current chunk of compiled bytecode.
Chunk* Compiler::currentChunk() {
	return _currentScope->function->getChunk();
}

/// Emit a byte in the current chunk bytecode.
void Compiler::emitByte(uint8_t byte) {
	currentChunk()->writeByte(byte);
}

/// Emit two bytes in the current chunk bytecode.
void Compiler::emitBytes(uint8_t byte1, uint8_t byte2) {
	emitByte(byte1);
	emitByte(byte2);
}

/// Emit a short value as two bytes in the current chunk bytecode.
void Compiler::emitShort(uint16_t shrt) {
	emitBytes(shrt & 0xff, shrt >> 8);
}

/// Emit a jump instruction in the current chunk bytecode.
///
/// Two sentinel bytes are emitted right after the OpCode byte. These two
/// bytes will store the 16-bit value of the jump code offset.
int Compiler::emitJump(uint8_t instruction) {
	emitByte(instruction);
	emitByte(0xff);
	emitByte(0xff);
	return currentChunk()->getCount() - 2;
}

/// Complete a jump instruction with the offset where the jump must fall.
///
/// The jump will fall at the offset right after the last code written in the
/// current chunk.
void Compiler::patchJump(int offset) {
	// Compute the code distance to jump
	int jump = currentChunk()->getCount() - offset - 2;

	// Check that the jump isn't too long
	if (jump > UINT16_MAX)
		error("Too much code to jump over");

	*currentChunk()->getCode(offset) = (jump >> 8) & 0xff;
	*currentChunk()->getCode(offset + 1) = jump & 0xff;
}

/// Emit an instruction in the current chunk bytecode.
///
/// An instruction is composed of an OpCode and an OpArg.
///
/// The OpArg may be 8-bit value, which will result in a single byte after
/// the OpCode. In the case of a 16-bit OpArg, the OP_EXTENDED_ARG OpCode
/// is emitted followed by the 8-bit complementary value to 0xff to form
/// the 16-bit OpArg value.
void Compiler::emitInstruction(uint8_t opcode, uint16_t oparg) {
	if (oparg < UINT8_MAX)
		emitBytes(opcode, oparg & 0xff);
	else {
		emitByte(OP_EXTENDED_ARG);
		emitBytes(opcode, oparg >> 8);
	}
}

/// Emit a return instruction in the current chunk bytecode.
///
/// A return instruction is composed of an OP_NULL OpCode followed by a
/// OP_RETURN OpCode.
void Compiler::emitReturn() {
	emitBytes(OP_NULL, OP_RETURN);
}

/// Emit an instruction in the current chunk bytecode for a constant in the
/// constant pool.
///
/// The value is added as a constant in the current chunk constant pool
/// before the instruction is emitted, so that its OpArg defines the index
/// of the constant in the constant pool.
void Compiler::emitConstant(Value value) {
	emitInstruction(OP_CONSTANT, makeConstant(value));
}

/// Add a constant in the current chunk constant pool.
uint16_t Compiler::makeConstant(Value value) {
	uint16_t constant = currentChunk()->addConstant(value);

	// Check that there is still space left in the constant pool
	if (constant > UINT16_MAX) {
		error("Too many constants in one chunk");
		return 0;
	}

	return constant;
}

/// Add a string object representation of an identifier to the constant pool
/// of the current chunk.
uint16_t Compiler::identifierConstant(ObjString *identifier) {
	return makeConstant(Value::object(identifier));
}

/// Convert a string to a Lax string object.
///
/// The string is interned in the string pool, so only one object is created
/// for each string. In case the string is already interned, a pointer to the
/// string object is returned.
ObjString* Compiler::copyIdentifier(const std::string &identifier) {
	return AS_STRING(Value::object(ObjString::copyString(identifier)));
}

/// Declare a variable in the current scope.
void Compiler::declareVariable(ObjString *name) {
	// A variable declared at top-level is global, not local
	if (_currentScope->depth == 0) return;

	// Check if the variable is not already declared in the current scope
	for (int i = _currentScope->localCount - 1; i >= 0; --i) {
		Local &local = _currentScope->locals[i];

		// Don't mind if the variable shadows an outer local variable or an uninitialized variable
		if (local.depth != -1 && local.depth > _currentScope->depth) break;

		// Raise an error if the local is already declared
		if (name == local.name)
			error("Variable already declared in this scope");
	}

	addLocal(name);
}

/// Define a variable in the current scope.
///
/// If the variable is local, then it is mark initialized. Otherwise,
/// that means the variable is global and an instruction is emitted to save
/// the global variable at runtime.
void Compiler::defineVariable(uint16_t global) {
	// Mark locals initialized in scopes other than the top-level
	if (_currentScope->depth > 0) {
		markLocalInitialized();
		return;
	}

	// Emit an instruction to define global variables
	emitInstruction(OP_DEFINE_GLOBAL, global);
}

/// Add a variable as a local in the current scope.
void Compiler::addLocal(ObjString *name) {
	// Check that there is still space left in the local variable array
	if (_currentScope->localCount == UINT8_MAX) {
		error("Too many local variables in scope");
		return;
	}

	// Add the variable as a local to the array
	Local &local = _currentScope->locals[_currentScope->localCount++];
	local.name = name;
	local.depth = -1; // Mark the local uninitialized, so that it cannot be referenced yet
	local.isCaptured = false;
}

/// Add a variable as an upvalue in a scope.
int Compiler::addUpvalue(Scope *scope, uint8_t index, bool isLocal) {
	int upvalueCount = scope->function->getUpvalueCount();

	// Check if the variable is not already in the upvalues array of the scope
	for (int i = 0; i < upvalueCount; ++i) {
		Upvalue &upvalue = scope->upvalues[i];

		if (upvalue.index == index && upvalue.isLocal == isLocal)
			return i;
	}

	// Check that there is still space left in the upvalue array
	if (upvalueCount == UINT8_MAX) {
		error("Too many closure variables in function");
		return 0;
	}

	// Add the variable as an upvalue to the array
	scope->upvalues[upvalueCount].isLocal = isLocal;
	scope->upvalues[upvalueCount].index = index;

	// Update the function counter for upvalues
	scope->function->incrementUpvalueCount();
	return scope->function->getUpvalueCount() - 1;
}

/// Mark the last declared local variable initialized, meaning it can be
/// referenced in the value of another variable.
void Compiler::markLocalInitialized() {
	// No local exists in the top-level scope
	if (_currentScope->depth == 0) return;

	// Mark the last local initialized
	_currentScope->locals[_currentScope->localCount - 1].depth = _currentScope->depth;
}

/// Look for the index of a local variable in a given scope.
int Compiler::resolveLocal(Scope *scope, ObjString *name) {
	// Look in all local variables, starting from the most recent ones
	for (int i = scope->localCount - 1; i >= 0; --i) {
		Local &local = scope->locals[i];

		// Local variable found
		if (name == local.name) {
			// Check if the variable is initialized
			if (local.depth == -1)
				error("Can't read local variable in its own initializer");

			// Return the index in the array of the variable
			return i;
		}
	}

	// Return a sentinel value to inform that the local hasn't been found
	return -1;
}

/// Look for the index of an upvalue in a given scope.
int Compiler::resolveUpvalue(Scope *scope, ObjString *name) {
	// No upvalue exists in the top-level scope
	if (scope->enclosing == nullptr) return -1;

	// First search in local variables of the enclosing scope
	int local = resolveLocal(scope->enclosing, name);

	// If found, mark the local as captured, so it can now be considered as an upvalue in the current scope
	if (local != -1) {
		scope->enclosing->locals[local].isCaptured = true;
		return addUpvalue(scope, static_cast<uint8_t>(local), true);
	}

	// Then search in upvalues of the enclosing scope
	int upvalue = resolveUpvalue(scope->enclosing, name);
	if (upvalue != -1) return addUpvalue(scope, static_cast<uint8_t>(upvalue), false);

	// Return a sentinel value to inform that the variable hasn't been found
	return -1;
}

/// Initialize a scope.
void Compiler::initScope(Scope *scope, FunctionType type) {
	// Initialize the scope
	scope->enclosing = _currentScope;
	scope->function = nullptr;
	scope->type = type;
	scope->localCount = 0;
	scope->depth = 0;
	scope->function = new ObjFunction(nullptr);

	_currentScope = scope;

	// Reserve the first local slot
	Local &local = _currentScope->locals[_currentScope->localCount++];
	local.depth = 0;
	local.name = nullptr;
	local.isCaptured = false;
}

/// End a scope and restore the enclosing scope.
ObjFunction* Compiler::endCurrentScope() {
	emitReturn();
	ObjFunction *function = _currentScope->function;

#ifdef DEBUG_PRINT_CODE
	if (!_errors) {
		disassembleChunk(currentChunk(), function->toString());
		std::cout << std::endl;
	} else {
		std::cout << "Errors during compilation of " << function->toString() << std::endl << std::endl;
	}
#endif

	_currentScope = _currentScope->enclosing;
	return function;
}

/// Begin a new local scope (mainly to depict a new block scope), thus
/// increasing the depth of future local variables in the current scope.
void Compiler::beginLocalScope() {
	_currentScope->depth++;
}

/// End the current local scope, and remove all locals and upvalues that were
/// created in this scope.
void Compiler::endLocalScope() {
	Scope *scope = _currentScope;
	scope->depth--;

	// Remove all locals and upvalues of the current local scope in the runtime stack
	while (scope->localCount > 0 && scope->locals[scope->localCount - 1].depth > scope->depth) {
		if (scope->locals[scope->localCount - 1].isCaptured)
			emitByte(OP_CLOSE_UPVALUE);
		else
			emitByte(OP_POP); // Remove local from stack
		scope->localCount--;
	}
}
/// Compile a StmtNode to bytecode
void Compiler::visit(StmtNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_STMTNODE
	Logger::warning("StmtNode");
#endif

	node.accept(*this);

#ifdef DEBUG_PRINT_COMPILATION_STMTNODE
	Logger::warning("StmtNode - end");
#endif
}

/// Compile an ExprNode to bytecode
void Compiler::visit(ExprNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_EXPRNODE
	Logger::warning("ExprNode");
#endif

	node.accept(*this);

#ifdef DEBUG_PRINT_COMPILATION_EXPRNODE
	Logger::warning("ExprNode - end");
#endif
}

/// Compile a StmtExpressionNode to bytecode
void Compiler::visit(StmtExpressionNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_STMTEXPRESSIONNODE
	Logger::warning("StmtExpressionNode");
#endif

	visit(*node.getExpr()); // Compile the expression
	emitByte(OP_POP); // Pop the result from the runtime stack

#ifdef DEBUG_PRINT_COMPILATION_STMTEXPRESSIONNODE
	Logger::warning("StmtExpressionNode - end");
#endif
}

/// Compile a BlockNode to bytecode
void Compiler::visit(BlockNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_BLOCKNODE
	Logger::warning("BlockNode");
#endif

	beginLocalScope(); // Begin a new scope at each block

	visit(*node.getSequence());

	endLocalScope(); // End the previously opened scope

#ifdef DEBUG_PRINT_COMPILATION_BLOCKNODE
	Logger::warning("BlockNode");
#endif
}

/// Compile a SeqNode to bytecode
void Compiler::visit(SeqNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_SEQNODE
	Logger::warning("SeqNode");
#endif
	auto& stmts = node.getStatements();

	// Compile each statement in the sequence
	for (const auto & stmt : stmts)
		visit(*stmt);

#ifdef DEBUG_PRINT_COMPILATION_SEQNODE
	Logger::warning("SeqNode - end");
#endif
}

/// Compile a DeclNode to bytecode
void Compiler::visit(DeclNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_DECLNODE
	Logger::warning("DeclNode: " + node->getId()->toString());
#endif

	ObjString *identifier = node.getName();
	declareVariable(identifier);

	// Compile the assigned value, if any
	if (node.getRValue())
		visit(*node.getRValue());
	else emitByte(OP_NULL); // Or assign null to the variable by default

	defineVariable(identifierConstant(identifier));

#ifdef DEBUG_PRINT_COMPILATION_DECLNODE
	Logger::warning("DeclNode - end");
#endif
}

/// Compile an AssignNode to bytecode
void Compiler::visit(AssignNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_ASSIGNNODE
	Logger::warning("AssignNode " + node->getName());
#endif

	ObjString *identifier = node.getName();

	// Search the identifier among declared local variables
	int arg = resolveLocal(_currentScope, identifier);

	// Compile the assigned expression
	visit(*node.getExpr());

	// Assign the value to the local variable found
	if (arg != -1)
		emitInstruction(OP_SET_LOCAL, static_cast<uint16_t>(arg));

    // Assign the value to the upvalue found
	else if ((arg = resolveUpvalue(_currentScope, identifier)) != -1) {
		emitInstruction(OP_SET_UPVALUE, static_cast<uint16_t>(arg));
	}

    // Assume that the variable is global and assign it the value
    // Note that the global variable might not exist depending on the runtime state
	else {
		arg = identifierConstant(identifier);
		emitInstruction(OP_SET_GLOBAL, static_cast<uint16_t>(arg));
	}

#ifdef DEBUG_PRINT_COMPILATION_ASSIGNNODE
	Logger::warning("AssignNode - end");
#endif
}

/// Compile an IdNode to bytecode
void Compiler::visit(IdNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_ID
	Logger::warning("Id: " + node->getName()->toString());
#endif

	ObjString *identifier = node.getName();

	// Search the identifier among declared local variables
	int arg = resolveLocal(_currentScope, identifier);

	// Get the value of the local variable found
	if (arg != -1)
		emitInstruction(OP_GET_LOCAL, static_cast<uint16_t>(arg));

	// Get the value of the upvalue found
	else if ((arg = resolveUpvalue(_currentScope, identifier)) != -1) {
		emitInstruction(OP_GET_UPVALUE, static_cast<uint16_t>(arg));
	}

	// Assume that the variable is global and get its value
	// Note that the global variable might not exist depending on the runtime state
	else {
		arg = identifierConstant(identifier);
		emitInstruction(OP_GET_GLOBAL, static_cast<uint16_t>(arg));
	}
}

/// Compile a ConditionalNode to bytecode
void Compiler::visit(ConditionalNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_CONDITIONALNODE
	Logger::warning("ConditionalNode");
#endif

	// Compile the conditional expression
	visit(*node.getConditionExpression());

	// Emit a jump over the then branch in case the condition is false
	int thenJump = emitJump(OP_JUMP_FALSE);
	emitByte(OP_POP); // Pop the condition result value from the runtime stack

	// Compile the statement executed if the condition is true
	visit(*node.getThenStatement());

	// Emit a jump over the bytecode for the else branch
	int elseJump = emitJump(OP_JUMP);

	patchJump(thenJump); // Fill the first jump so that it knows where to jump to overfly the then branch
	emitByte(OP_POP); // Pop the condition result value from the runtime stack (the previous pop didn't occur)

	// Compile the else branch, if any
	if (node.getElseStatement())
		visit(*node.getElseStatement());

	patchJump(elseJump); // Fill the first jump so that it knows where to jump to overfly the else branch

#ifdef DEBUG_PRINT_COMPILATION_CONDITIONALNODE
	Logger::warning("ConditionalNode - end");
#endif
}

/// Compile a LogicalNode to bytecode
void Compiler::visit(LogicalNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_LOGICALNODE
	Logger::warning("LogicalNode");
#endif

	TokenType operatorType = node.getToken()->getType();

	// Compile the left operand
	// The right operand is not compiled yet to enable short-circuit
	visit(*node.getLeft());

	switch (operatorType) {
		case TokenType::AND: {
			// Emit a jump in case the left operand is false
			int endJump = emitJump(OP_JUMP_FALSE);

			//
			// Bytecode in case left operand is true ; will not be executed at runtime if false
			//

			emitByte(OP_POP); // Pop the operand result from the runtime stack
			visit(*node.getRight()); // Compile the right operand

			//
			// End of bytecode for case true
			//

			// Fill the previous jump so that it knows where to jump if the operand was false
			patchJump(endJump);
//			emitByte(OP_POP); // Pop the operand result from the runtime stack
			break;
		}
		case TokenType::OR: {
			// Emit a jump in case the left operand is false
			int elseJump = emitJump(OP_JUMP_FALSE);
			// Emit a jump in case the left operand is true
			int endJump = emitJump(OP_JUMP);

			//
			// Bytecode in case left operand is false ; will not be executed at runtime if true
			//

			patchJump(elseJump); // Fill the first jump so that it knows where to jump if the operand was false
			emitByte(OP_POP); // Pop the operand result from the runtime stack

			visit(*node.getRight()); // Compile the right operand
			patchJump(endJump); // Fill the second jump so that it knows where to jump if the operand was true

			//
			// End of bytecode for case false
			//
			break;
		}
		default: return; // Unreachable
	}

#ifdef DEBUG_PRINT_COMPILATION_LOGICALNODE
	Logger::warning("LogicalNode - end");
#endif
}

/// Compile a RelationalNode to bytecode
void Compiler::visit(RelationalNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_RELATIONALNODE
	Logger::warning("RelationalNode");
#endif

	TokenType operatorType = node.getToken()->getType();

	// Compile both operands
	visit(*node.getLeft());
	visit(*node.getRight());

	// Emit the operation instruction
	switch (operatorType) {
		case TokenType::EQ:			emitByte(OP_EQUAL); break;
		case TokenType::NEQ:		emitByte(OP_NOT_EQUAL); break;
		case TokenType::SL:			emitByte(OP_LESS); break;
		case TokenType::LE:			emitByte(OP_LESS_EQUAL); break;
		case TokenType::SG:			emitByte(OP_GREATER); break;
		case TokenType::GE:			emitByte(OP_GREATER_EQUAL); break;
		default: return; // Unreachable
	}

#ifdef DEBUG_PRINT_COMPILATION_RELATIONALNODE
	Logger::warning("RelationalNode - end");
#endif
}

/// Compile a FunNode to bytecode
void Compiler::visit(FunNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_FUNNODE
	Logger::warning("FunNode: " + node->getName()->toString());
#endif

	ObjString *identifier = node.getName();
	declareVariable(identifier);

	// Mark the function initialized so that it can be called inside itself
	// This is allows recursive calls of local functions
	markLocalInitialized();

	// Create a new scope for the function
	Scope scope;
	initScope(&scope, TYPE_FUNCTION);
	beginLocalScope();

	int paramCount = 0;

	// Declare all parameters as local variables in the function scope
	for (int i = 0; i < node.getParams().size(); ++i) {
		ObjString *paramIdentifier = copyIdentifier((node.getParams()[i]->getVarName()->toString()));
		declareVariable(paramIdentifier);
		defineVariable(identifierConstant(paramIdentifier));
		++paramCount;
	}

	scope.function = new ObjFunction(identifier, paramCount);

	// Compile the function body
	visit(*node.getBody());

	// Close the function scope and wrap the function in a function object
	ObjFunction *function = endCurrentScope();

	// Emit a closure to capture at runtime all local variables from surrounding scopes
	emitInstruction(OP_CLOSURE, makeConstant(Value::object(function)));

	// Capture all upvalues
	for (int i = 0; i < function->getUpvalueCount(); ++i) {
		emitByte(scope.upvalues[i].isLocal ? 1 : 0);
		emitByte(scope.upvalues[i].index);
	}

	// Finally, define top-level functions in the global scope
	defineVariable(identifierConstant(identifier));

#ifdef DEBUG_PRINT_COMPILATION_FUNNODE
	Logger::warning("FunNode - end");
#endif
}

/// Compile a CallNode to bytecode
void Compiler::visit(CallNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_CALLNODE
	Logger::warning("CallNode");
#endif

	// Compile the callee
	visit(*node.getCallee());

	// Counter for the number of arguments passed to the call
	uint8_t argCount = 0;

	for (int i = 0; i < node.getArgs().size(); ++i) {
		visit(*node.getArgs()[i].get()); // Compile the argument
		++argCount;
	}

	// Emit an instruction for the function call
	emitInstruction(OP_CALL, argCount);

#ifdef DEBUG_PRINT_COMPILATION_CALLNODE
	Logger::warning("CallNode - end");
#endif
}

/// Compile a ReturnNode to bytecode
void Compiler::visit(ReturnNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_RETURNNODE
	Logger::warning("ReturnNode");
#endif

	// Check that the return instruction doesn't occur at top-level
	if (_currentScope->type == FunctionType::TYPE_SCRIPT)
		error("Can't return from top-level code");

	// Compile the value returned, if any
	if (node.getValue()) {
		visit(*node.getValue());
		emitByte(OP_RETURN);
	} else emitReturn(); // Or simply return null by default

#ifdef DEBUG_PRINT_COMPILATION_RETURNNODE
	Logger::warning("ReturnNode - end");
#endif
}

/// Compile a BinOpNode to bytecode
void Compiler::visit(BinOpNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_BINOPNODE
	Logger::warning("BinOpNode");
#endif

	TokenType operatorType = node.getToken()->getType();

	// Compile both operands
	visit(*node.getLeft());
	visit(*node.getRight());

	// Emit the operation instruction
	switch (operatorType) {
		case TokenType::PLUS: 		emitByte(OP_ADD); break;
		case TokenType::MINUS: 		emitByte(OP_SUBTRACT); break;
		case TokenType::STAR: 		emitByte(OP_MULTIPLY); break;
		case TokenType::SLASH: 		emitByte(OP_DIVIDE); break;
		default: return; // Unreachable
	}

#ifdef DEBUG_PRINT_COMPILATION_BINOPNODE
	Logger::warning("BinOpNode - end");
#endif
}

/// Compile an UnaryNode to bytecode
void Compiler::visit(UnaryNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_UNARYNODE
	Logger::warning("UnaryNode");
#endif

	TokenType operatorType = node.getToken()->getType();

	// Compile the operand
	visit(*node.getExpr());

	// Emit the operation instruction
	switch (operatorType) {
		case TokenType::BANG: 		emitByte(OP_NOT); break;
		case TokenType::MINUS: 		emitByte(OP_NEGATE); break;
		default: return; // Unreachable
	}

#ifdef DEBUG_PRINT_COMPILATION_UNARYNODE
	Logger::warning("UnaryNode - end");
#endif
}

/// Compile a LiteralNode to bytecode
void Compiler::visit(LiteralNode &node) {
#ifdef DEBUG_PRINT_COMPILATION_LITERALNODE
	Value v = node->getValue();
	Logger::warning("LiteralNode: " + Value::toString(v));
#endif

	emitConstant(node.getValue());
}

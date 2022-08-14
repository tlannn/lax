#ifndef LAX_COMPILER_H
#define LAX_COMPILER_H

#include <fstream>

#ifdef DEBUG_TRACE_EXECUTION
#include "common/Debug.h"
#endif

#include "ast/ASTVisitor.h"
#include "common/AST.h"

// Forward declarations
class Chunk;
class ObjFunction;
class ObjString;

/**
 * Compiler that traverse an Abstract Syntax Tree to convert it to bytecode
 */
class Compiler : public ASTVisitor {
public:
	/// Class constructor.
	Compiler();

	/**
	 * Compile an AST to bytecode.
	 *
	 * @param ast the AST to compile.
	 * @return the function object representing the script, and containing the
	 * bytecode.
	 */
	ObjFunction* compile(ASTNode *ast);

	bool writeBytecode(Chunk *chunk);

private:
	/// Local variable representation.
	typedef struct {
		ObjString *name;
		int depth;
		bool isCaptured;
	} Local;

	/// Upvalue representation.
	typedef struct {
		uint8_t index;
		bool isLocal;
	} Upvalue;

	/// Enumeration of types of function.
	typedef enum {
		TYPE_FUNCTION,
		TYPE_SCRIPT
	} FunctionType;

	/// Scope representation.
	typedef struct Scope {
		struct Scope *enclosing;
		ObjFunction *function;
		FunctionType type;
		Upvalue upvalues[UINT8_MAX];
		Local locals[UINT8_MAX];
		int localCount;
		int depth;
	} Scope;

	/**
	 * Report an error.
	 *
	 * @param message the error message.
	 */
	void error(const std::string &message);

	/**
	 * Return the current chunk of compiled bytecode.
	 *
	 * @return the current chunk of bytecode.
	 */
	Chunk* currentChunk();

	/**
	 * Emit a byte in the current chunk bytecode.
	 *
	 * @param byte the byte to emit.
	 */
	void emitByte(uint8_t byte);

	/**
	 * Emit two bytes in the current chunk bytecode.
	 *
	 * Byte byte1 is emitted before byte byte2.
	 *
	 * @param byte1 the first byte emitted.
	 * @param byte2 the second byte emitted.
	 */
	void emitBytes(uint8_t byte1, uint8_t byte2);

	/**
	 * Emit a short value as two bytes in the current chunk bytecode.
	 *
	 * Byte byte1 is emitted before byte byte2.
	 * @param shrt the first byte emitted.
	 */
	void emitShort(uint16_t shrt);

	/**
	 * Emit a jump instruction in the current chunk bytecode.
	 *
	 * Two sentinel bytes are emitted right after the OpCode byte. These two
	 * bytes will store the 16-bit value of the jump code offset.
	 *
	 * @param instruction the jump instruction OpCode.
	 * @return the offset in the bytecode of the jump code offset.
	 */
	int emitJump(uint8_t instruction);

	/**
	 * Complete a jump instruction with the offset where the jump must fall.
	 * The jump will fall at the offset right after the last code written in the
	 * current chunk.
	 *
	 * @param offset the offset in the current chunk bytecode of the jump code
	 * offset to complete.
	 */
	void patchJump(int offset);

	/**
	 * Emit a loop instruction in the current chunk bytecode.
	 *
	 * The offset in the bytecode where the loop must go back to is stored as
	 * an 16-bit OpArg.
	 *
	 * @param loopStart the offset in the bytecode where the loop must jump
	 */
	void emitLoop(int loopStart);

	/**
	 * Emit an instruction in the current chunk bytecode.
	 *
	 * An instruction is composed of an OpCode and an OpArg.
	 *
	 * The OpArg may be 8-bit value, which will result in a single byte after
	 * the OpCode. In the case of a 16-bit OpArg, the OP_EXTENDED_ARG OpCode
	 * is emitted followed by the 8-bit complementary value to 0xff to form
	 * the 16-bit OpArg value.
	 *
	 * @param opcode the OpCode of the instruction.
	 * @param oparg the OpArg of the instruction.
	 */
	void emitInstruction(uint8_t opcode, uint16_t oparg);

	/**
	 * Emit a return instruction in the current chunk bytecode.
	 *
	 * A return instruction is composed of an OP_NULL OpCode followed by a
	 * OP_RETURN OpCode.
	 */
	void emitReturn();

	/**
	 * Emit an instruction in the current chunk bytecode for a constant in the
	 * constant pool.
	 *
	 * The value is added as a constant in the current chunk constant pool
	 * before the instruction is emitted, so that its OpArg defines the index
	 * of the constant in the constant pool.
	 *
	 * @param value the constant value in the constant pool.
	 */
	void emitConstant(Value value);

	/**
	 * Add a constant in the current chunk constant pool.
	 *
	 * @param value the value to add.
	 * @return the index of the new constant in the constant pool.
	 */
	uint16_t makeConstant(Value value);

	/**
	 * Add a string object representation of an identifier to the constant pool
	 * of the current chunk.
	 *
	 * @param identifier the string object of the identifier.
	 * @return the index of the new constant in the constant pool.
	 */
	uint16_t identifierConstant(ObjString *identifier);

	/**
	 * Convert a string to a Lax string object.
	 *
	 * The string is interned in the string pool, so only one object is created
	 * for each string. In case the string is already interned, a pointer to the
	 * string object is returned.
	 *
	 * @param identifier the string identifier.
	 * @return a pointer to the interned string object representing the string.
	 */
	static ObjString* copyIdentifier(const std::string &identifier);

	/**
	 * Declare a variable in the current scope.
	 *
	 * @param name the name of the variable.
	 */
	void declareVariable(ObjString *name);

	/**
	 * Define a variable in the current scope.
	 *
	 * If the variable is local, then it is mark initialized. Otherwise,
	 * that means the variable is global and an instruction is emitted to save
	 * the global variable at runtime.
	 *
	 * @param global the index of the variable in the constant pool.
	 */
	void defineVariable(uint16_t global);

	/**
	 * Add a variable as a local in the current scope.
	 *
	 * @param name the name of the variable.
	 */
	void addLocal(ObjString *name);

	/**
	 * Add a variable as an upvalue in a scope.
	 *
	 * @param scope the scope to add the upvalue to.
	 * @param index the index of the variable in the local variables array of
	 * the scope.
	 * @param isLocal whether the variable is a local or an upvalue in the
	 * enclosing scope.
	 * @return the index of the upvalue in the scope array.
	 */
	int addUpvalue(Scope *scope, uint8_t index, bool isLocal);

	/**
	 * Mark the last declared local variable initialized, meaning it can be
	 * referenced in the value of another variable.
	 */
	void markLocalInitialized();

	/**
	 * Look for the index of a local variable in a given scope.
	 *
	 * @param scope the scope where to search for the local variable.
	 * @param name the name of the local variable.
	 * @return the local index in the scope's local array, or -1 if the local
	 * does not exist.
	 */
	int resolveLocal(Scope *scope, ObjString *name);

	/**
	 * Look for the index of an upvalue in a given scope.
	 *
	 * @param scope the scope where to search for the upvalue.
	 * @param name the name of variable captured by the upvalue.
	 * @return the upvalue index in the scope's upvalues array, or -1 if the
	 * variable does not exist.
	 */
	int resolveUpvalue(Scope *scope, ObjString *name);

	/**
	 * Initialize a scope.
	 *
	 * @param scope the scope to initialize.
	 * @param type the type of function depicted by scope.
	 */
	void initScope(Scope *scope, FunctionType type);

	/**
	 * End a scope and restore the enclosing scope.
	 *
	 * @return the function object depicted by the scope closed.
	 */
	ObjFunction* endCurrentScope();

	/**
	 * Begin a new local scope (mainly to depict a new block scope), thus
	 * increasing the depth of future local variables in the current scope.
	 */
	void beginLocalScope();

	/**
	 * End the current local scope, and remove all locals and upvalues that were
	 * created in this scope.
	 */
	void endLocalScope();

	/// Compile a StmtNode to bytecode
	void visit(StmtNode *node) override;

	/// Compile an ExprNode to bytecode
	void visit(ExprNode *node) override;

	/// Compile a StmtExpressionNode to bytecode
	void visit(StmtExpressionNode *node) override;

	/// Compile a BlockNode to bytecode
	void visit(BlockNode *node) override;

	/// Compile a SeqNode to bytecode
	void visit(SeqNode *node) override;

	/// Compile a DeclNode to bytecode
	void visit(DeclNode *node) override;

	/// Compile an AssignNode to bytecode
	void visit(AssignNode *node) override;

	/// Compile an IdNode to bytecode
	void visit(IdNode *node) override;

	/// Compile a whileNode to bytecode
	void visit(WhileLoopNode *node) override;

	/// Compile a ForNode to bytecode
	void visit(ForLoopNode *node) override;

	/// Compile a ConditionalNode to bytecode
	void visit(ConditionalNode *node) override;

	/// Compile a LogicalNode to bytecode
	void visit(LogicalNode *node) override;

	/// Compile a RelationalNode to bytecode
	void visit(RelationalNode *node) override;

	/// Compile a FunNode to bytecode
	void visit(FunNode *node) override;

	/// Compile a CallNode to bytecode
	void visit(CallNode *node) override;

	/// Compile a ReturnNode to bytecode
	void visit(ReturnNode *node) override;

	/// Compile a BinOpNode to bytecode
	void visit(BinOpNode *node) override;

	/// Compile an UnaryNode to bytecode
	void visit(UnaryNode *node) override;

	/// Compile a LiteralNode to bytecode
	void visit(LiteralNode *node) override;

	/*
	 * Private members
	 */

	Scope *_currentScope;
	bool _errors;
};

#endif //LAX_COMPILER_H

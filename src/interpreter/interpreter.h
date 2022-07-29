#ifndef LAX_INTERPRETER_H
#define LAX_INTERPRETER_H

#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

#include "callframe.h"
#include "return.h"
#include "runtimeerror.h"
#include "ast/astvisitor.h"
#include "ast/astnode.h"
#include "ast/exprnode.h"
#include "ast/assignnode.h"
#include "ast/binopnode.h"
#include "ast/callnode.h"
#include "ast/funnode.h"
#include "ast/literalnode.h"
#include "ast/id.h"
#include "ast/declnode.h"
#include "ast/logicalnode.h"
#include "ast/relationalnode.h"
#include "ast/conditionalnode.h"
#include "ast/stmtnode.h"
#include "ast/blocknode.h"
#include "ast/seqnode.h"
#include "ast/returnnode.h"
#include "ast/stmtexpressionnode.h"
#include "ast/stmtprintnode.h"
#include "ast/unarynode.h"
#include "common/value.h"
#include "objects/callable.h"
#include "objects/objfunction.h"
#include "objects/objclosure.h"
#include "objects/object.h"
#include "objects/objstring.h"
#include "symbols/env.h"
#include "symbols/symboltable.h"
#include "utils/logger.h"

/**
 * Interpreter for the Lax language
 *
 * Implements the ASTVisitor interface.
 * The role of the interpreter is to visit an Abstract Syntax Tree and simulate
 * the execution of the program represented. It defines methods that describe how
 * nodes of an AST must be handled.
 */
class Interpreter : public ASTVisitor {
public:
	/**
	 * Class constructor
	 *
	 * @param parser
	 */
	explicit Interpreter(ASTNode *ast);

	/**
	 * Interpret the code parsed by the parser
	 */
	void interpret();

	/**
	 * Visit an ExprNode and determine the value to which it can be reduced
	 */
	void visit(ExprNode *node) override;

	/**
	 * Visit a BinOpNode and compute the operation represented by the node
	 */
	void visit(BinOpNode *node) override;

	/**
	 * Visit a LogicalNode and compute the boolean value represented by the
	 * boolean expression
	 */
	void visit(LogicalNode *node) override;

	/**
	 * Visit a RelationalNode and compute the resulting boolean value
	 * according to the truthiness of the equality or inequality
	 */
	void visit(RelationalNode *node) override;

	/**
	 * Visit a LiteralNode and determine the literal value represented
	 */
	void visit(LiteralNode *node) override;

	/**
	 * Visit an Id and determine the value of the variable defined with this
	 * identifier
	 */
	void visit(Id *node) override;

	/**
	 * Visit a CallNode and evaluate the call
	 */
	void visit(CallNode *node) override;

	/**
	 * Visit an UnaryNode and determine the resulting literal value
	 */
	void visit(UnaryNode *node) override;

	/**
	 * Visit a StmtNode and execute the statement
	 */
	void visit(StmtNode *node) override;

	/**
	 * Visit a BlockNode and execute the sequence of statements inside it
	 */
	void visit(BlockNode *node) override;

	/**
	 * Visit a SeqNode and execute all the statements inside it
	 */
	void visit(SeqNode *node) override;

	/**
	 * Visit a DeclNode and declare a variable
	 */
	void visit(DeclNode *node) override;

	/**
	 * Visit an AssignNode and assign a new value to a variable
	 */
	void visit(AssignNode *node) override;

	/**
	 * Visit a FunNode and save its function definition
	 */
	void visit(FunNode *node) override;

	/**
	 * Visit a ConditionalNode and execute the 'then' statement referenced
	 * if the condition is evaluated to true, otherwise execute the 'else'
	 * statement if there is one
	 */
	void visit(ConditionalNode *node) override;

	/**
	 * Visit a ReturnNode and return from a function
	 */
	void visit(ReturnNode *node) override;

	/**
	 * Visit a StmtPrintNode and print the result of an expression
	 */
	void visit(StmtPrintNode *node) override;

	/**
	 * Visit a StmtExpressionNode and reduce an expression
	 */
	void visit(StmtExpressionNode *node) override;

	/**
	 * Execute the instructions inside a block
	 * @param node the node representing the block code
	 * @param frame the frame where variables must be saved
	 */
	void executeBlock(BlockNode *node, CallFrame *frame);

private:
	ASTNode *_ast;
	Value _result;
	CallFrame *_frame;
};

#endif // LAX_INTERPRETER_H

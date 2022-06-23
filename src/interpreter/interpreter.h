#ifndef LAX_INTERPRETER_H
#define LAX_INTERPRETER_H

#include <vector>

#include "exprvisitor.h"
#include "stmtvisitor.h"
#include "ast/exprnode.h"
#include "ast/assignnode.h"
#include "ast/binopnode.h"
#include "ast/literalnode.h"
#include "ast/declnode.h"
#include "ast/logicalnode.h"
#include "ast/relationalnode.h"
#include "ast/conditionalnode.h"
#include "ast/stmtnode.h"
#include "ast/blocknode.h"
#include "ast/stmtexpressionnode.h"
#include "ast/stmtprintnode.h"
#include "parser/parser.h"
#include "symbols/symboltable.h"

/**
 * Interpreter for the Lax language
 *
 * Implements the ExprVisitor and StmtVisitor visitor interfaces.
 * The role of the interpreter is to visit an Abstract Syntax Tree and simulate
 * the execution of the program represented. It defines methods that describe how
 * nodes of an AST must be handled.
 */
class Interpreter : public ExprVisitor, StmtVisitor {
public:
	/**
	 * Class constructor
	 *
	 * @param parser
	 */
	explicit Interpreter(Parser &parser);

	/// Interpret the code parsed by the parser
	void interpret();

	/// Evaluate an expression node and return the value to which it has been reduced
	int evaluate(ExprNode *node) override;

	/// Visit a BinOpNode and compute the operation represented by the node
	int visit(BinOpNode *node) override;

	/// Visit a LiteralNode and return the literal value represented
	int visit(LiteralNode *node) override;

	/// Visit a LogicalNode and return the boolean value represented by the boolean expression
	int visit(LogicalNode *node) override;

	/// Visit a RelationalNode and return a boolean value according to the truthiness of the equality or inequality
	int visit(RelationalNode *node) override;

	/// Visit an Id (identifier) and return the value of the variable defined with this identifier
	int visit(Id *node) override;

	/// Execute a statement node
	void execute(StmtNode *node) override;

	/// Visit a StmtExpressionNode node and compute the expression in the statement
	void visit(StmtExpressionNode *node) override;

	/// Visit a StmtPrintNode node and print the result of the expression in the statement
	void visit(StmtPrintNode *node) override;

	/// Visit a ConditionalNode and execute the 'then' statement referenced if the condition
	/// is evaluated to true, otherwise execute the 'else' statement if there is one
	void visit(ConditionalNode *node) override;

	/// Visit a DeclNode and declare a variable
	void visit(DeclNode *node) override;

	/// Visit an AssignNode and assign a new value to a variable
	void visit(AssignNode *node) override;

	/// Visit a BlockNode and execute all the statements inside the block
	void visit(BlockNode *node) override;

private:
	Parser _parser;
	std::unordered_map<std::string, int> _memory;
};

#endif // LAX_INTERPRETER_H

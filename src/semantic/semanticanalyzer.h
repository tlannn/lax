#ifndef LAX_SEMANTICANALYZER_H
#define LAX_SEMANTICANALYZER_H

#include "parser/parser.h"
#include "interpreter/exprvisitor.h"
#include "interpreter/stmtvisitor.h"

class SemanticAnalyzer : public ExprVisitor, StmtVisitor {
public:
    /**
     * Class constructor
     *
     * @param parser
     */
    explicit SemanticAnalyzer(Parser &parser);

    /// Interpret the program parsed by the parser
    void analyze();

    /// Evaluate an expression node and return the value to which it has been reduced
    int evaluate(ExprNode *node) override;

    /// Visit a BinOpNode and compute the operation represented by the node
    int visit(BinOpNode *node) override;

    /// Visit a LogicalNode and return the boolean value represented by the boolean expression
    int visit(LogicalNode *node) override;

    /// Visit a RelationalNode and return a boolean value according to the truthiness of the equality or inequality
    int visit(RelationalNode *node) override;

	/// Visit a LiteralNode and return the literal value represented
	int visit(LiteralNode *node) override;

	/// Visit an Id (identifier) and return the value of the variable defined with this identifier
	int visit(Id *node) override;

	/// Execute a statement node
    void execute(StmtNode *node) override;

	/// Visit a BlockNode and execute all the statements inside the block
	void visit(BlockNode *node) override;

	/// Visit a DeclNode and declare a variable
	void visit(DeclNode *node) override;

	/// Visit an AssignNode and assign a new value to a variable
	void visit(AssignNode *node) override;

	/// Visit a ConditionalNode and execute the 'then' statement referenced if the condition
	/// is evaluated to true, otherwise execute the 'else' statement if there is one
	void visit(ConditionalNode *node) override;

    /// Visit a StmtPrintNode node and print the result of the expression in the statement
    void visit(StmtPrintNode *node) override;

	/// Visit a StmtExpressionNode node and compute the expression in the statement
	void visit(StmtExpressionNode *node) override;

private:
    Parser _parser;
	Env *_env;
	Type _resultType;
};

#endif // LAX_SEMANTICANALYZER_H

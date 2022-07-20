#ifndef LAX_SEMANTICANALYZER_H
#define LAX_SEMANTICANALYZER_H

#include <memory>

#include "semanticerror.h"
#include "ast/astnode.h"
#include "ast/exprnode.h"
#include "ast/assignnode.h"
#include "ast/binopnode.h"
#include "ast/literalnode.h"
#include "ast/id.h"
#include "ast/declnode.h"
#include "ast/logicalnode.h"
#include "ast/relationalnode.h"
#include "ast/conditionalnode.h"
#include "ast/stmtnode.h"
#include "ast/blocknode.h"
#include "ast/seqnode.h"
#include "ast/stmtexpressionnode.h"
#include "ast/stmtprintnode.h"
#include "ast/unarynode.h"
#include "lexer/lexer.h"
#include "interpreter/astvisitor.h"
#include "symbols/env.h"
#include "symbols/varsymbol.h"
#include "utils/logger.h"

class SemanticAnalyzer : public ASTVisitor {
public:
    /**
     * Class constructor
     *
     * @param parser
     */
    explicit SemanticAnalyzer(ASTNode *ast);

	/**
	 * Class destructor
	 */
	~SemanticAnalyzer();

    /**
     * Analyze semantically the code parsed by the parser
     */
    void analyze();

	/**
	 * Return whether errors occurred during semantic analysis
	 * @return true if errors occurred
	 */
	bool hadErrors() const;

	/**
	 * Return an exception on a specific token
	 *
	 * @param token the token that raised the error
	 * @param message the error message
	 * @param type the type of error
	 * @return an exception
	 */
	SemanticError error(Token *token, const std::string &message, const std::string &type);

	/**
	 * Report an error to inform the user
	 * @param error the error
	 */
	static void report(const SemanticError &err);

    /// Evaluate an expression node and return the value to which it has been reduced
	void visit(ExprNode *node) override;

    /// Visit a BinOpNode and compute the operation represented by the node
	void visit(BinOpNode *node) override;

    /// Visit a LogicalNode and return the boolean value represented by the boolean expression
	void visit(LogicalNode *node) override;

    /// Visit a RelationalNode and return a boolean value according to the truthiness of the equality or inequality
	void visit(RelationalNode *node) override;

	/// Visit a LiteralNode and return the literal value represented
	void visit(LiteralNode *node) override;

	/// Visit an Id (identifier) and return the value of the variable defined with this identifier
	void visit(Id *node) override;

	/// Visit an unary expression and return the literal value
	void visit(UnaryNode *node) override;

	/// Execute a statement node
    void visit(StmtNode *node) override;

	/// Visit a BlockNode and execute the sequence of statements inside it
	void visit(BlockNode *node) override;

	/// Visit a SeqNode and execute all the statements inside it
	void visit(SeqNode *node) override;

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
	ASTNode *_ast; // The root node of the AST
	Env *_env; // The environment that keeps track of identifiers used
	Type _resultType; // The type of the result of the last node visited
	bool _errors; // Becomes true when an error occurs
};

#endif // LAX_SEMANTICANALYZER_H

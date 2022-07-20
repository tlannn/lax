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

    /**
     * Visit an ExprNode and determine the type of the value to which it
     * has been reduced
     */
	void visit(ExprNode *node) override;

    /**
     * Visit a BinOpNode and determine the type of the result computed by the
     * operation represented by the node
     */
	void visit(BinOpNode *node) override;

    /**
     * Visit a LogicalNode and set the type of the expression as boolean
     */
	void visit(LogicalNode *node) override;

    /**
     * Visit a RelationalNode and set the type of the expression as boolean
     */
	void visit(RelationalNode *node) override;

	/**
	 * Visit a LiteralNode and determine the type of the literal
	 */
	void visit(LiteralNode *node) override;

	/**
	 * Visit an Id and determine the type of the value associated
	 */
	void visit(Id *node) override;

	/**
	 * Visit an UnaryNode and determine the type of the literal
	 */
	void visit(UnaryNode *node) override;

	/**
	 * Visit a StmtNode and check semantics inside it
	 */
    void visit(StmtNode *node) override;

	/**
     * Visit a BlockNode and check semantics in the sequence of statements
     * inside it
     */
	void visit(BlockNode *node) override;

	/**
     * Visit a SeqNode and check semantics in all statements inside it
     */
	void visit(SeqNode *node) override;

	/**
	 * Visit a DeclNode and create a symbol associated to the variable created
	 * to keep track of its type
	 */
	void visit(DeclNode *node) override;

	/**
	 * Visit an AssignNode and check that the new value is type-consistent, and
	 * if needed, update the type of the variable symbol
	 */
	void visit(AssignNode *node) override;

	/**
	 * Visit a ConditionalNode and check symbols in both branches 'then'
	 * and 'else'
	 */
	void visit(ConditionalNode *node) override;

    /**
     * Visit a StmtPrintNode and check semantics in the expression to print
     */
    void visit(StmtPrintNode *node) override;

	/**
     * Visit a StmtExpressionNode and check semantics in the expression
     */
	void visit(StmtExpressionNode *node) override;

private:
	ASTNode *_ast; // The root node of the AST
	Env *_env; // The environment that keeps track of identifiers used
	Type _resultType; // The type of the result of the last node visited
	bool _errors; // Becomes true when an error occurs
};

#endif // LAX_SEMANTICANALYZER_H

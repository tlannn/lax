#ifndef LAX_SEMANTICANALYZER_H
#define LAX_SEMANTICANALYZER_H

#include <memory>

#include "SemanticError.h"
#include "ast/ASTVisitor.h"
#include "ast/nodes/ASTNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/nodes/AssignNode.h"
#include "ast/nodes/BinOpNode.h"
#include "ast/nodes/CallNode.h"
#include "ast/nodes/FunNode.h"
#include "ast/nodes/LiteralNode.h"
#include "ast/nodes/IdNode.h"
#include "ast/nodes/DeclNode.h"
#include "ast/nodes/LogicalNode.h"
#include "ast/nodes/RelationalNode.h"
#include "ast/nodes/ConditionalNode.h"
#include "ast/nodes/StmtNode.h"
#include "ast/nodes/BlockNode.h"
#include "ast/nodes/SeqNode.h"
#include "ast/nodes/ReturnNode.h"
#include "ast/nodes/StmtExpressionNode.h"
#include "ast/nodes/UnaryNode.h"
#include "lexer/Lexer.h"
#include "objects/Object.h"
#include "symbols/Env.h"
#include "symbols/FunSymbol.h"
#include "symbols/VarSymbol.h"
#include "utils/Logger.h"

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
	 * Visit an AssignNode and check that the new value is type-consistent, and
	 * if needed, update the type of the variable symbol
	 */
	void visit(AssignNode *node) override;

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
	 * Visit an UnaryNode and determine the type of the literal
	 */
	void visit(UnaryNode *node) override;

	/**
     * Visit a CallNode and check if the function called is defined
     */
	void visit(CallNode *node) override;

	/**
	 * Visit a LiteralNode and determine the type of the literal
	 */
	void visit(LiteralNode *node) override;

	/**
	 * Visit an IdNode and determine the type of the value associated
	 */
	void visit(IdNode *node) override;

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
	 * Visit a ConditionalNode and check symbols in both branches 'then'
	 * and 'else'
	 */
	void visit(ConditionalNode *node) override;

	/**
	 * Visit a WhileNode and check symbols in the condition and body of the loop
	 */
	void visit(WhileNode *node) override;

	/**
	 * Visit a ForNode and check symbols in the header and body of the loop
	 */
	void visit(ForNode *node) override;

	/**
     * Visit a FunNode and define a function in the environment
     */
	void visit(FunNode *node) override;

	/**
	 * Visit a ReturnNode and exit a function call by returning a value
	 */
	void visit(ReturnNode *node) override;

	/**
     * Visit a StmtExpressionNode and check semantics in the expression
     */
	void visit(StmtExpressionNode *node) override;

private:
	ASTNode *_ast; // The root node of the AST
	Env *_env; // The environment that keeps track of identifiers used
	ValueType _resultType; // The type of the result of the last node visited
	bool _errors; // Becomes true when an error occurs
};

#endif // LAX_SEMANTICANALYZER_H

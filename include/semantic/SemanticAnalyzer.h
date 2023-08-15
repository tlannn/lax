#ifndef LAX_SEMANTICANALYZER_H
#define LAX_SEMANTICANALYZER_H

#include <memory>

#include "SemanticError.h"
#include "ast/ASTFwdDecl.h"
#include "ast/ASTVisitor.h"
#include "lexer/Lexer.h"
#include "objects/Object.h"
#include "symbols/FunSymbol.h"
#include "symbols/VarSymbol.h"
#include "utils/Logger.h"

// Forward declarations
class SymbolTable;
class AST;

class SemanticAnalyzer : public ASTVisitor {
public:
    /**
     * Class constructor
     *
     * @param parser
     */
    explicit SemanticAnalyzer(AST &ast);

	/**
	 * Class destructor
	 */
	~SemanticAnalyzer() = default;

    /**
     * Analyze semantically the code parsed by the parser
     */
    virtual void analyze();

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

    void visit(ExprNode &node) override;

    void visit(AssignNode &node) override;

    void visit(LogicalNode &node) override;

    void visit(RelationalNode &node) override;

    void visit(BinOpNode &node) override;

    void visit(UnaryNode &node) override;

    void visit(CallNode &node) override;

    void visit(LiteralNode &node) override;

    void visit(IdNode &node) override;

    void visit(StmtNode &node) override;

    void visit(BlockNode &node) override;

    void visit(SeqNode &node) override;

    void visit(DeclNode &node) override;

    void visit(ConditionalNode &node) override;

    void visit(FunNode &node) override;

    void visit(ReturnNode &node) override;

    void visit(StmtExpressionNode &node) override;

protected:
	AST &_ast; // The AST to analyze
	bool _errors; // Becomes true when an error occurs
    std::shared_ptr<SymbolTable> m_symtable;
};

#endif // LAX_SEMANTICANALYZER_H

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

/**
 * @class SemanticAnalyzer
 * @brief Analyzes the AST semantically.
 *
 * The SemanticAnalyzer class is used to analyze the AST semantically. It
 * implements the ASTVisitor interface to visit each node of the AST and
 * analyze it.
 *
 * @see ASTVisitor
 */
class SemanticAnalyzer : public ASTVisitor {
public:
    /**
     * @brief Class constructor.
     *
     * Constructs a semantic analyzer with a given AST.
     *
     * @param ast The AST to analyze.
     */
    explicit SemanticAnalyzer(AST& ast);

    /**
     * @brief Class destructor.
     *
     * Default destructor.
     */
    ~SemanticAnalyzer() = default;

    /**
     * @brief Analyzes the AST.
     *
     * This function analyzes the AST semantically. It visits each node of the
     * AST and analyzes it.
     */
    virtual void analyze();

    /**
     * @brief Checks if the analyzer had any errors.
     *
     * This function checks if the analyzer had any errors during the analysis.
     *
     * @return `true` if the analyzer had any errors, `false` otherwise.
     */
    bool hadErrors() const;

    /**
     * @brief Returns an exception on a specific token.
     *
     * @param token The token that raised the error.
     * @param message The error message.
     * @param type The type of error.
     * @return The exception.
     */
    SemanticError error(Token* token, const std::string& message,
        const std::string& type);

    /**
     * @brief Reports an error to inform the user.
     * @param error The error.
     */
    static void report(const SemanticError& err);

    /**
     * @copydoc ASTVisitor::visit(ExprNode&)
     */
    void visit(ExprNode& node) override;

    /**
     * @copydoc ASTVisitor::visit(AssignNode&)
     */
    void visit(AssignNode& node) override;

    /**
     * @copydoc ASTVisitor::visit(LogicalNode&)
     */
    void visit(LogicalNode& node) override;

    /**
     * @copydoc ASTVisitor::visit(RelationalNode&)
     */
    void visit(RelationalNode& node) override;

    /**
     * @copydoc ASTVisitor::visit(BinOpNode&)
     */
    void visit(BinOpNode& node) override;

    /**
     * @copydoc ASTVisitor::visit(UnaryNode&)
     */
    void visit(UnaryNode& node) override;

    /**
     * @copydoc ASTVisitor::visit(CallNode&)
     */
    void visit(CallNode& node) override;

    /**
     * @copydoc ASTVisitor::visit(LiteralNode&)
     */
    void visit(LiteralNode& node) override;

    /**
     * @copydoc ASTVisitor::visit(IdNode&)
     */
    void visit(IdNode& node) override;

    /**
     * @copydoc ASTVisitor::visit(StmtNode&)
     */
    void visit(StmtNode& node) override;

    /**
     * @copydoc ASTVisitor::visit(BlockNode&)
     */
    void visit(BlockNode& node) override;

    /**
     * @copydoc ASTVisitor::visit(SeqNode&)
     */
    void visit(SeqNode& node) override;

    /**
     * @copydoc ASTVisitor::visit(DeclNode&)
     */
    void visit(DeclNode& node) override;

    /**
     * @copydoc ASTVisitor::visit(ConditionalNode&)
     */
    void visit(ConditionalNode& node) override;

    /**
     * @copydoc ASTVisitor::visit(FunNode&)
     */
    void visit(FunNode& node) override;

    /**
     * @copydoc ASTVisitor::visit(ReturnNode&)
     */
    void visit(ReturnNode& node) override;

    /**
     * @copydoc ASTVisitor::visit(StmtExpressionNode&)
     */
    void visit(StmtExpressionNode& node) override;

protected:
    AST& m_ast; // The AST to analyze
    bool m_errors; // Becomes true when an error occurs
    std::shared_ptr<SymbolTable> m_symtable;
};

#endif // LAX_SEMANTICANALYZER_H

#ifndef LAX_TOP_LEVEL_DEFINER_H
#define LAX_TOP_LEVEL_DEFINER_H

#include "SemanticAnalyzer.h"

// Forward declarations
class AST;
class ASTNode;

/**
 * @brief Resolves identifiers at the top level of the source code.
 *
 *
 */
class TopLevelDefiner : public SemanticAnalyzer {
public:
    explicit TopLevelDefiner(AST& ast);

    virtual ~TopLevelDefiner() = default;

private:
    //void visit(ExprNode& node) override;

    //void visit(AssignNode& node) override;

    //void visit(CallNode& node) override;

    //void visit(IdNode& node) override;

    void visit(StmtNode& node) override;

    //void visit(BlockNode& node) override;

    void visit(DeclNode& node) override;

    void visit(FunNode& node) override;

public:
    void visit(StmtExpressionNode& node) override;

private:
    /**
     * @brief Binds the current scope to the given node.
     * @param node The node to bind the scope to.
     */
    void bindScope(ASTNode& node);
};

#endif // LAX_TOP_LEVEL_DEFINER_H

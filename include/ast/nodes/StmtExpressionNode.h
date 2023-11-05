#ifndef LAX_STMTEXPRESSIONNODE_H
#define LAX_STMTEXPRESSIONNODE_H

#include <memory>

#include "StmtNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;

/**
 * @class StmtExpressionNode
 * @brief Represents an expression statement in the Abstract Syntax Tree (AST).
 *
 * The StmtExpressionNode class is used to store information about an expression
 * statement. An expression statement is used to evaluate an expression.
 *
 * The node stores the expression to visit.
 */
class StmtExpressionNode : public StmtNode {
public:
    /**
     * @brief Class constructor.
     * @param expr The expression to visit.
     */
    explicit StmtExpressionNode(UExprNode expr);

    /**
     * @brief Retrieves the expression to visit.
     * @return The expression to visit.
     */
    ExprNode* getExpr();

    /**
     * @copydoc ASTNode::accept()
     */
    void accept(ASTVisitor& visitor) override;

protected:
    UExprNode m_expr;
};

#endif // LAX_STMTEXPRESSIONNODE_H

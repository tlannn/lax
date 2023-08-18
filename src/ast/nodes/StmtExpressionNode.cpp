#include "ast/nodes/StmtExpressionNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor
StmtExpressionNode::StmtExpressionNode(UExprNode expr) :
    m_expr(std::move(expr)) {}

/// Getter for the expression to visit
ExprNode* StmtExpressionNode::getExpr() {
    return m_expr.get();
}

/// Accept method for the visitor pattern
void StmtExpressionNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

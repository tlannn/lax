#include "ast/nodes/StmtExpressionNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"

StmtExpressionNode::StmtExpressionNode(UExprNode expr) :
    m_expr(std::move(expr)) {}

ExprNode* StmtExpressionNode::getExpr() {
    return m_expr.get();
}

void StmtExpressionNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

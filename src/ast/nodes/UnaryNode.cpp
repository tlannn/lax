#include "ast/nodes/UnaryNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"

UnaryNode::UnaryNode(SToken op, UExprNode expr) : ExprNode(std::move(op)),
    m_expr(std::move(expr)) {}

ExprNode* UnaryNode::getExpr() const {
    return m_expr.get();
}

void UnaryNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

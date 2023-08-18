#include "ast/nodes/UnaryNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor
UnaryNode::UnaryNode(SToken op, UExprNode expr) : ExprNode(std::move(op)),
    m_expr(std::move(expr)) {}

/// Getter for the expression of the operation
ExprNode* UnaryNode::getExpr() const {
    return m_expr.get();
}

/// Accept method for the visitor pattern
void UnaryNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

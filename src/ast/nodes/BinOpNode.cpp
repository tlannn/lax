#include "ast/nodes/BinOpNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor
BinOpNode::BinOpNode(UExprNode left, SToken op, UExprNode right) :
    ExprNode(std::move(op)),
    m_left(std::move(left)),
    m_right(std::move(right)) {}

/// Getter for the left expression of the operation
ExprNode* BinOpNode::getLeft() {
    return m_left.get();
}

/// Getter for the right expression of the operation
ExprNode* BinOpNode::getRight() {
    return m_right.get();
}

/// Accept method for the visitor pattern
void BinOpNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

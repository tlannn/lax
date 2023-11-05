#include "ast/nodes/BinOpNode.h"
#include "ast/ASTVisitor.h"

BinOpNode::BinOpNode(UExprNode left, SToken op, UExprNode right) :
    ExprNode(std::move(op)),
    m_left(std::move(left)),
    m_right(std::move(right)) {}

ExprNode* BinOpNode::getLeft() {
    return m_left.get();
}

ExprNode* BinOpNode::getRight() {
    return m_right.get();
}

void BinOpNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

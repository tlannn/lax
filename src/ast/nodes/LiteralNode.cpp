#include "ast/nodes/LiteralNode.h"
#include "ast/ASTVisitor.h"

LiteralNode::LiteralNode(SToken token, Value value) : ExprNode(std::move(token)),
    m_value(value) {}

Value LiteralNode::getValue() {
    return m_value;
}

void LiteralNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

#include "ast/nodes/LiteralNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor
LiteralNode::LiteralNode(SToken token, Value value) : ExprNode(std::move(token)),
    m_value(value) {}

/// Getter for the value of the literal
Value LiteralNode::getValue() {
    return m_value;
}

/// Accept method for the visitor pattern
void LiteralNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

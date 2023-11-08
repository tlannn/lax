#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"

ExprNode::ExprNode(UToken token) :
    m_token(std::move(token)) {}

Token* ExprNode::getToken() {
    return m_token.get();
}

void ExprNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

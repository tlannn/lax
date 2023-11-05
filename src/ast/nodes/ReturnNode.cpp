#include "ast/nodes/ReturnNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"
#include "tokens/Token.h"

ReturnNode::ReturnNode(UToken returnToken, UExprNode value) :
    m_returnToken(std::move(returnToken)),
    m_value(std::move(value)) {}

Token* ReturnNode::getToken() {
    return m_returnToken.get();
}

ExprNode* ReturnNode::getValue() {
    return m_value.get();
}

void ReturnNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

#include "ast/nodes/DeclNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"

DeclNode::DeclNode(std::shared_ptr<Token> token, ObjString* name, LaxType* type,
    UExprNode expr) :
    m_id(std::move(token)),
    m_name(name),
    m_type(type),
    m_rvalue(std::move(expr)),
    m_symbol(nullptr) {}

Token* DeclNode::getToken() {
    return m_id.get();
}

ObjString* DeclNode::getName() {
    return m_name;
}

LaxType* DeclNode::getType() {
    return m_type;
}

ExprNode* DeclNode::getRValue() {
    return m_rvalue.get();
}

VarSymbol* DeclNode::getSymbol() {
    return m_symbol;
}

void DeclNode::setSymbol(VarSymbol* symbol) {
    m_symbol = symbol;
}

void DeclNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

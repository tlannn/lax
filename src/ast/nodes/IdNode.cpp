#include "ast/nodes/IdNode.h"
#include "ast/ASTVisitor.h"
#include "objects/ObjString.h"

IdNode::IdNode(UToken name) : ExprNode(std::move(name)),
    m_name(ObjString::copyString(ExprNode::getToken()->toString())),
    m_symbol(nullptr) {}

ObjString* IdNode::getName() {
    return m_name;
}

Symbol* IdNode::getSymbol() const {
    return m_symbol;
}

void IdNode::setSymbol(Symbol* symbol) {
    m_symbol = symbol;
}

void IdNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

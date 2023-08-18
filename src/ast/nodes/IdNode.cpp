#include "ast/nodes/IdNode.h"
#include "ast/ASTVisitor.h"
#include "objects/ObjString.h"

/// Class constructor
IdNode::IdNode(SToken name) : ExprNode(std::move(name)),
    m_name(ObjString::copyString(ExprNode::getToken()->toString())),
    m_symbol(nullptr) {}

/// Getter for the name of the identifier
ObjString* IdNode::getName() {
    return m_name;
}

/// Getter for the symbol representing the variable referred to
Symbol* IdNode::getSymbol() const {
    return m_symbol;
}

/// Setter for the symbol representing the variable referred to
void IdNode::setSymbol(Symbol* symbol) {
    m_symbol = symbol;
}

/// Accept method for the visitor pattern
void IdNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

#include "ast/nodes/DeclNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor
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

/// Getter for the name of the variable declared
ObjString* DeclNode::getName() {
    return m_name;
}

/// Getter for the type of the variable declared
LaxType* DeclNode::getType() {
    return m_type;
}

/// Getter for the expression associated to the variable at declaration
ExprNode* DeclNode::getRValue() {
    return m_rvalue.get();
}

/// Getter for the symbol representing the variable
VarSymbol* DeclNode::getSymbol() {
    return m_symbol;
}

/// Setter for the symbol representing the variable
void DeclNode::setSymbol(VarSymbol* symbol) {
    m_symbol = symbol;
}

/// Accept method for the visitor pattern
void DeclNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

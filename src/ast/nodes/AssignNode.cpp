#include "ast/nodes/AssignNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor
AssignNode::AssignNode(ObjString* identifier, SToken assignToken,
    UExprNode expr) :
    ExprNode(std::move(assignToken)),
    m_identifier(identifier),
    m_expr(std::move(expr)),
    m_symbol(nullptr) {}

/// Getter for the token of the variable
ObjString* AssignNode::getName() {
    return m_identifier;
}

/// Getter for the new expression assigned
ExprNode* AssignNode::getExpr() {
    return m_expr.get();
}

/// Getter for the symbol representing the variable assigned
VarSymbol* AssignNode::getSymbol() const {
    return m_symbol;
}

/// Setter for the symbol representing the variable assigned
void AssignNode::setSymbol(VarSymbol* symbol) {
    m_symbol = symbol;
}

/// Accept method for the visitor pattern
void AssignNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

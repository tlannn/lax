#include "ast/nodes/AssignNode.h"
#include "ast/ASTVisitor.h"

AssignNode::AssignNode(ObjString* identifier, SToken assignToken,
    UExprNode expr) :
    ExprNode(std::move(assignToken)),
    m_identifier(identifier),
    m_expr(std::move(expr)),
    m_symbol(nullptr) {}

ObjString* AssignNode::getVariableName() {
    return m_identifier;
}

ExprNode* AssignNode::getExpr() {
    return m_expr.get();
}

VarSymbol* AssignNode::getSymbol() const {
    return m_symbol;
}

void AssignNode::setSymbol(VarSymbol* symbol) {
    m_symbol = symbol;
}

void AssignNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

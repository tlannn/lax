#include "ast/nodes/AssignNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor
AssignNode::AssignNode(ObjString *identifier, SToken assignToken, UExprNode expr) :
	ExprNode(std::move(assignToken)),
	_identifier(identifier),
	_expr(std::move(expr)),
    _symbol(nullptr) {}

/// Getter for the token of the variable
ObjString* AssignNode::getName() {
    return _identifier;
}

/// Getter for the new expression assigned
ExprNode* AssignNode::getExpr() {
    return _expr.get();
}

/// Getter for the symbol representing the variable assigned
VarSymbol *AssignNode::getSymbol() const {
    return _symbol;
}

/// Setter for the symbol representing the variable assigned
void AssignNode::setSymbol(VarSymbol *symbol) {
    _symbol = symbol;
}

/// Accept method for the visitor pattern
void AssignNode::accept(ASTVisitor &visitor) {
	visitor.visit(*this);
}

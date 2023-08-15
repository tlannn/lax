#include "ast/nodes/DeclNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor
DeclNode::DeclNode(std::shared_ptr<Token> token, ObjString *name, LaxType* type, UExprNode expr) :
	_id(std::move(token)), _name(name), _type(type), _rvalue(std::move(expr)) {}

Token* DeclNode::getToken() {
    return _id.get();
}

/// Getter for the name of the variable declared
ObjString* DeclNode::getName() {
    return _name;
}

/// Getter for the type of the variable declared
LaxType* DeclNode::getType() {
    return _type;
}

/// Getter for the expression associated to the variable at declaration
ExprNode* DeclNode::getRValue() {
    return _rvalue.get();
}

/// Getter for the symbol representing the variable
VarSymbol* DeclNode::getSymbol() {
    return _symbol;
}

/// Setter for the symbol representing the variable
void DeclNode::setSymbol(VarSymbol* symbol) {
    _symbol = symbol;
}

/// Accept method for the visitor pattern
void DeclNode::accept(ASTVisitor &visitor) {
    visitor.visit(*this);
}

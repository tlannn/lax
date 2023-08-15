#include "ast/nodes/IdNode.h"
#include "ast/ASTVisitor.h"
#include "objects/ObjString.h"
#include "tokens/Token.h"

/// Class constructor
IdNode::IdNode(SToken name) :
	ExprNode(std::move(name)),
	_name(ObjString::copyString(ExprNode::getToken()->toString())),
    _symbol(nullptr) {}

/// Getter for the name of the identifier
ObjString* IdNode::getName() {
	return _name;
}

/// Getter for the symbol representing the variable referred to
Symbol* IdNode::getSymbol() const {
    return _symbol;
}

/// Setter for the symbol representing the variable referred to
void IdNode::setSymbol(Symbol *symbol) {
    _symbol = symbol;
}

/// Accept method for the visitor pattern
void IdNode::accept(ASTVisitor &visitor) {
    visitor.visit(*this);
}

#include "declnode.h"

/// Class constructor
DeclNode::DeclNode(std::shared_ptr<Token> id, Type type, std::unique_ptr<ExprNode> expr) :
	_id(std::move(id)), _type(type), _rvalue(std::move(expr)) {}

/// Getter for the name of the variable declared
std::shared_ptr<Token> DeclNode::getId() {
    return _id;
}

/// Getter for the type of the variable declared
Type DeclNode::getType() {
    return _type;
}

/// Getter for the expression associated to the variable at declaration
ExprNode* DeclNode::getRValue() {
    return _rvalue.get();
}

/// Accept method for the visitor pattern
void DeclNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

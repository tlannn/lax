#include "ast/nodes/DeclNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor
DeclNode::DeclNode(std::shared_ptr<Token> id, ValueType type, UExprNode expr) :
	_id(std::move(id)), _type(type), _rvalue(std::move(expr)) {}

/// Getter for the name of the variable declared
std::shared_ptr<Token> DeclNode::getId() {
    return _id;
}

/// Getter for the type of the variable declared
ValueType DeclNode::getType() {
    return _type;
}

/// Getter for the expression associated to the variable at declaration
ExprNode* DeclNode::getRValue() {
    return _rvalue.get();
}

/// Accept method for the visitor pattern
void DeclNode::accept(ASTVisitor &visitor) {
    visitor.visit(*this);
}

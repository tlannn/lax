#include "declnode.h"

/// DeclNode constructor
DeclNode::DeclNode(Token* id, Type type, ExprNode *expr) : _id(id), _type(type), _rvalue(expr) {}

/// Getter for the name of the variable declared
Token* DeclNode::getId() {
    return _id;
}

/// Getter for the type of the variable declared
Type DeclNode::getType() {
    return _type;
}

/// Getter for the expression associated to the variable at declaration
ExprNode* DeclNode::getRValue() {
    return _rvalue;
}

/// Accept method for the visitor pattern
void DeclNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

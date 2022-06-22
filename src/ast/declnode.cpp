#include "declnode.h"

/// DeclNode constructor
DeclNode::DeclNode(std::string name, Type type, ExprNode *expr) : _name(name), _type(type), _rvalue(expr) {}

/// Getter for the name of the variable declared
std::string DeclNode::getName() {
    return _name;
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
void DeclNode::accept(StmtVisitor *visitor) {
    visitor->visit(this);
}

#include "relationalnode.h"

/// RelationalNode constructor
RelationalNode::RelationalNode(ExprNode *left, Token op, ExprNode *right) : LogicalNode(left, op, right) {
    // Override logical node type check logic
    _type = check(left->getType(), right->getType());
}

/// Accept method for the visitor pattern
int RelationalNode::accept(ExprVisitor *visitor) {
    return visitor->visit(this);
}

/// Check if the expression can result in a boolean expression
Type RelationalNode::check(Type t1, Type t2) {
    if (t1 == t2) return Type::BOOL;
    else if (t1 != Type::BOOL) return t1;
    else return t2;
}

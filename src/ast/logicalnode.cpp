#include "logicalnode.h"

/// LogicalNode constructor
LogicalNode::LogicalNode(ExprNode *left, Token op, ExprNode *right) : ExprNode(op, check(left->getType(), right->getType())), _left(left), _right(right) {}

/// Getter for the left expression of the boolean operation
ExprNode* LogicalNode::getLeft() {
    return _left;
}

/// Getter for the right expression of the boolean operation
ExprNode* LogicalNode::getRight() {
    return _right;
}

/// Accept method for the visitor pattern
int LogicalNode::accept(ExprVisitor *visitor) {
    return visitor->visit(this);
}

/// Check if the expression can result in a boolean expression
Type LogicalNode::check(Type t1, Type t2) {
    if (t1 != Type::BOOL) return t1;
    else if (t2 != Type::BOOL) return t2;
    else return Type::BOOL;
}

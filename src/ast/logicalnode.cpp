#include "logicalnode.h"

/// LogicalNode constructor
LogicalNode::LogicalNode(ExprNode *left, Token op, ExprNode *right) : ExprNode(op), _left(left), _right(right) {}

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

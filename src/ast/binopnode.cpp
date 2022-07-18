#include "binopnode.h"

/// BinOpNode constructor
BinOpNode::BinOpNode(ExprNode *left, Token *op, ExprNode *right) : ExprNode(op), _left(left), _right(right) {}

/// Getter for the left expression of the operation
ExprNode* BinOpNode::getLeft() {
    return _left;
}

/// Getter for the right expression of the operation
ExprNode* BinOpNode::getRight() {
    return _right;
}

/// Accept method for the visitor pattern
void BinOpNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

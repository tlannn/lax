#include "binopnode.h"

/// Class constructor
BinOpNode::BinOpNode(std::unique_ptr<ExprNode> left, std::unique_ptr<Token> op, std::unique_ptr<ExprNode> right) :
	ExprNode(op.get()), _left(std::move(left)), _op(std::move(op)), _right(std::move(right)) {}

/// Getter for the left expression of the operation
ExprNode* BinOpNode::getLeft() {
    return _left.get();
}

/// Getter for the right expression of the operation
ExprNode* BinOpNode::getRight() {
    return _right.get();
}

/// Getter for the operator of the operation
Token* BinOpNode::getOperator() {
	return _op.get();
}

/// Accept method for the visitor pattern
void BinOpNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

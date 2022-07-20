#include "logicalnode.h"

/// Class constructor
LogicalNode::LogicalNode(std::unique_ptr<ExprNode> left, std::unique_ptr<Token> op, std::unique_ptr<ExprNode> right) :
	ExprNode(std::move(op)), _left(std::move(left)), _right(std::move(right)) {}

/// Getter for the left expression of the boolean operation
ExprNode* LogicalNode::getLeft() {
    return _left.get();
}

/// Getter for the right expression of the boolean operation
ExprNode* LogicalNode::getRight() {
    return _right.get();
}

/// Accept method for the visitor pattern
void LogicalNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

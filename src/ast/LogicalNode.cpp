#include "ast/LogicalNode.h"

/// Class constructor
LogicalNode::LogicalNode(std::unique_ptr<ExprNode> left, std::unique_ptr<Token> op, std::unique_ptr<ExprNode> right) :
	BinOpNode(std::move(left), std::move(op), std::move(right)) {}

/// Accept method for the visitor pattern
void LogicalNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

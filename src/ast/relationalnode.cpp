#include "relationalnode.h"

/// Class constructor
RelationalNode::RelationalNode(
		std::unique_ptr<ExprNode> left, std::unique_ptr<Token> op, std::unique_ptr<ExprNode> right) :
		LogicalNode(std::move(left), std::move(op), std::move(right)) {}

/// Accept method for the visitor pattern
void RelationalNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

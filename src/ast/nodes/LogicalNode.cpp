#include "ast/nodes/LogicalNode.h"
#include "ast/ASTVisitor.h"
#include "tokens/Token.h"

/// Class constructor
LogicalNode::LogicalNode(UExprNode left, UToken op, UExprNode right) :
	BinOpNode(std::move(left), std::move(op), std::move(right)) {}

/// Accept method for the visitor pattern
void LogicalNode::accept(ASTVisitor &visitor) {
    visitor.visit(*this);
}

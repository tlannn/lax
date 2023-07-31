#include "ast/nodes/RelationalNode.h"
#include "ast/ASTVisitor.h"
#include "tokens/Token.h"

/// Class constructor
RelationalNode::RelationalNode(UExprNode left, UToken op, UExprNode right) :
		LogicalNode(std::move(left), std::move(op), std::move(right)) {}

/// Accept method for the visitor pattern
void RelationalNode::accept(ASTVisitor &visitor) {
    visitor.visit(*this);
}

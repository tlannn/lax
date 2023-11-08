#include "ast/nodes/RelationalNode.h"
#include "ast/ASTVisitor.h"

RelationalNode::RelationalNode(UExprNode left, UToken op, UExprNode right) :
    LogicalNode(std::move(left), std::move(op), std::move(right)) {}

void RelationalNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

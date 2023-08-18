#include "ast/nodes/RelationalNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor
RelationalNode::RelationalNode(UExprNode left, SToken op, UExprNode right) :
    LogicalNode(std::move(left), std::move(op), std::move(right)) {}

/// Accept method for the visitor pattern
void RelationalNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

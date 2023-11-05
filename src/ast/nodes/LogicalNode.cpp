#include "ast/nodes/LogicalNode.h"
#include "ast/ASTVisitor.h"

LogicalNode::LogicalNode(UExprNode left, SToken op, UExprNode right) :
    BinOpNode(std::move(left), std::move(op), std::move(right)) {}

void LogicalNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

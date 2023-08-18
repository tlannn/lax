#include "ast/nodes/StmtNode.h"
#include "ast/ASTVisitor.h"

/// Accept method for the visitor pattern
void StmtNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

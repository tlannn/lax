#include "ast/nodes/StmtNode.h"
#include "ast/ASTVisitor.h"

void StmtNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

#include "ast/StmtNode.h"

/// Accept method for the visitor pattern
void StmtNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

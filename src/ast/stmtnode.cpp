#include "stmtnode.h"

/// Abstract accept method for the visitor pattern
void StmtNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

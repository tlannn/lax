#include "seqnode.h"

/// SeqNode constructor
SeqNode::SeqNode(std::vector<StmtNode *> stmts) : _stmts(stmts) {}

/// Getter for the statements to execute
std::vector<StmtNode *> SeqNode::getStatements() {
	return _stmts;
}

/// Accept method for the visitor pattern
void SeqNode::accept(StmtVisitor *visitor) {
	visitor->visit(this);
}

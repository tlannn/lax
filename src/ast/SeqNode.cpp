#include "ast/SeqNode.h"

/// Class constructor
SeqNode::SeqNode(std::vector<std::unique_ptr<StmtNode>> stmts) : _stmts(std::move(stmts)) {}

/// Getter for the statements to execute
const std::vector<std::unique_ptr<StmtNode>>& SeqNode::getStatements() {
	return _stmts;
}

/// Accept method for the visitor pattern
void SeqNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

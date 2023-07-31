#include "ast/nodes/SeqNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor
SeqNode::SeqNode(std::vector<UStmtNode> stmts) : _stmts(std::move(stmts)) {}

/// Getter for the statements to execute
const std::vector<UStmtNode>& SeqNode::getStatements() {
	return _stmts;
}

/// Accept method for the visitor pattern
void SeqNode::accept(ASTVisitor &visitor) {
    visitor.visit(*this);
}

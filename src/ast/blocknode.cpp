#include "blocknode.h"

/// BlockNode constructor
BlockNode::BlockNode(std::vector<StmtNode*> stmts) : _stmts(stmts) {}

/// Getter for the statements inside the block
std::vector<StmtNode*> BlockNode::getStatements() {
    return _stmts;
}

/// Accept method for the visitor pattern
void BlockNode::accept(StmtVisitor *visitor) {
    visitor->visit(this);
}

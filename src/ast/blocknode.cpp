#include "blocknode.h"

/// BlockNode constructor
BlockNode::BlockNode(SeqNode *seq) : _seq(seq) {}

/// Getter for the sequence of statements inside the block
SeqNode* BlockNode::getSequence() {
    return _seq;
}

/// Accept method for the visitor pattern
void BlockNode::accept(StmtVisitor *visitor) {
    visitor->visit(this);
}

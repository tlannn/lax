#include "blocknode.h"

/// Class constructor
BlockNode::BlockNode(std::unique_ptr<SeqNode> seq) : _seq(std::move(seq)) {}

/// Getter for the sequence of statements inside the block
SeqNode* BlockNode::getSequence() {
    return _seq.get();
}

/// Accept method for the visitor pattern
void BlockNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

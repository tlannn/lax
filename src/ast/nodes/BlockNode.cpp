#include "ast/nodes/BlockNode.h"
#include "ast/ASTVisitor.h"
#include "ast/nodes/SeqNode.h"

/// Class constructor
BlockNode::BlockNode(USeqNode seq) : _seq(std::move(seq)) {}

/// Getter for the sequence of statements inside the block
SeqNode* BlockNode::getSequence() {
    return _seq.get();
}

/// Accept method for the visitor pattern
void BlockNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

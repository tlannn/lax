#include "ast/nodes/BlockNode.h"
#include "ast/nodes/SeqNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor
BlockNode::BlockNode(USeqNode seq) :
    m_seq(std::move(seq)) {}

/// Getter for the sequence of statements inside the block
SeqNode* BlockNode::getSequence() {
    return m_seq.get();
}

/// Accept method for the visitor pattern
void BlockNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

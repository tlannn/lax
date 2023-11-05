#include "ast/nodes/BlockNode.h"
#include "ast/nodes/SeqNode.h"
#include "ast/ASTVisitor.h"

BlockNode::BlockNode(USeqNode seq) :
    m_seq(std::move(seq)) {}

SeqNode* BlockNode::getSequence() {
    return m_seq.get();
}

void BlockNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

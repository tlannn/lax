#include "ast/nodes/SeqNode.h"
#include "ast/ASTVisitor.h"

SeqNode::SeqNode(std::vector<UStmtNode> stmts) :
    m_stmts(std::move(stmts)) {}

const std::vector<UStmtNode>& SeqNode::getStatements() {
    return m_stmts;
}

void SeqNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

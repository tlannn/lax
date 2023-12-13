#include "ast/nodes/SeqNode.h"
#include "ast/ASTVisitor.h"

SeqNode::SeqNode(std::list<UStmtNode> stmts) :
    m_stmts(std::move(stmts)) {}

const std::list<UStmtNode>& SeqNode::getStatements() {
    return m_stmts;
}

void SeqNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

void SeqNode::moveToFront(std::list<UStmtNode>::const_iterator it) {
    m_stmts.splice(m_stmts.begin(), m_stmts, it);
}

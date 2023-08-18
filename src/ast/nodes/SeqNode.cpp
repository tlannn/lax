#include "ast/nodes/SeqNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor
SeqNode::SeqNode(std::vector<UStmtNode> stmts) :
    m_stmts(std::move(stmts)) {}

/// Getter for the statements to execute
const std::vector<UStmtNode>& SeqNode::getStatements() {
    return m_stmts;
}

/// Accept method for the visitor pattern
void SeqNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

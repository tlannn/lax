#include "ast/nodes/ConditionalNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"

ConditionalNode::ConditionalNode(UExprNode expr, UStmtNode thenStmt,
    UStmtNode elseStmt) :
    m_expr(std::move(expr)),
    m_thenStmt(std::move(thenStmt)),
    m_elseStmt(std::move(elseStmt)) {}

ExprNode* ConditionalNode::getConditionExpression() {
    return m_expr.get();
}

StmtNode* ConditionalNode::getThenStatement() {
    return m_thenStmt.get();
}

StmtNode* ConditionalNode::getElseStatement() {
    return m_elseStmt.get();
}

void ConditionalNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

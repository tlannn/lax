#include "ast/nodes/ConditionalNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor
ConditionalNode::ConditionalNode(UExprNode expr, UStmtNode thenStmt,
    UStmtNode elseStmt) :
    m_expr(std::move(expr)),
    m_thenStmt(std::move(thenStmt)),
    m_elseStmt(std::move(elseStmt)) {}

/// Getter for the condition expression
ExprNode* ConditionalNode::getConditionExpression() {
    return m_expr.get();
}

/// Getter for the 'then' statement
StmtNode* ConditionalNode::getThenStatement() {
    return m_thenStmt.get();
}

/// Getter for the 'else' statement
StmtNode* ConditionalNode::getElseStatement() {
    return m_elseStmt.get();
}

/// Accept method for the visitor pattern
void ConditionalNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

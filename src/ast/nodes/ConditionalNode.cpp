#include "ast/nodes/ConditionalNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor
ConditionalNode::ConditionalNode(UExprNode expr, UStmtNode thenStmt, UStmtNode elseStmt) :
		StmtNode(), _expr(std::move(expr)), _thenStmt(std::move(thenStmt)), _elseStmt(std::move(elseStmt)) {}

/// Getter for the condition expression
ExprNode* ConditionalNode::getConditionExpression() {
    return _expr.get();
}

/// Getter for the 'then' statement
StmtNode* ConditionalNode::getThenStatement() {
    return _thenStmt.get();
}

/// Getter for the 'else' statement
StmtNode* ConditionalNode::getElseStatement() {
    return _elseStmt.get();
}

/// Accept method for the visitor pattern
void ConditionalNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

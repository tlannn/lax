#include "conditionalnode.h"

/// ConditionalNode constructor
ConditionalNode::ConditionalNode(ExprNode *expr, StmtNode *thenStmt, StmtNode *elseStmt) : StmtNode(),
	_expr(expr), _thenStmt(thenStmt), _elseStmt(elseStmt) {}

/// Getter for the condition expression
ExprNode* ConditionalNode::getConditionExpression() {
    return _expr;
}

/// Getter for the 'then' statement
StmtNode* ConditionalNode::getThenStatement() {
    return _thenStmt;
}

/// Getter for the 'else' statement
StmtNode* ConditionalNode::getElseStatement() {
    return _elseStmt;
}

/// Accept method for the visitor pattern
void ConditionalNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

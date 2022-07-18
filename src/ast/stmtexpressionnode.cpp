#include "stmtexpressionnode.h"

/// StmtExpressionNode constructor
StmtExpressionNode::StmtExpressionNode(ExprNode *expr) : _expr(expr) {}

/// Getter for the expression to visit
ExprNode* StmtExpressionNode::getExpr() {
    return _expr;
}

/// Accept method for the visitor pattern
void StmtExpressionNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

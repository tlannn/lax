#include "stmtexpressionnode.h"

/// Class constructor
StmtExpressionNode::StmtExpressionNode(std::unique_ptr<ExprNode> expr) : _expr(std::move(expr)) {}

/// Getter for the expression to visit
ExprNode* StmtExpressionNode::getExpr() {
    return _expr.get();
}

/// Accept method for the visitor pattern
void StmtExpressionNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

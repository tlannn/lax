#include "stmtprintnode.h"

/// Class constructor
StmtPrintNode::StmtPrintNode(std::unique_ptr<ExprNode> expr) : _expr(std::move(expr)) {}

/// Getter for the expression to print
ExprNode* StmtPrintNode::getExpr() {
    return _expr.get();
}

/// Accept method for the visitor pattern
void StmtPrintNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

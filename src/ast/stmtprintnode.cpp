#include "stmtprintnode.h"

/// StmtPrintNode constructor
StmtPrintNode::StmtPrintNode(ExprNode *expr) : _expr(expr) {}

/// Getter for the expression to print
ExprNode* StmtPrintNode::getExpr() {
    return _expr;
}

/// Accept method for the visitor pattern
void StmtPrintNode::accept(StmtVisitor *visitor) {
    visitor->visit(this);
}

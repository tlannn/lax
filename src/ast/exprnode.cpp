#include "exprnode.h"

/// ExprNode constructor
ExprNode::ExprNode(Token tok) : _tok(tok) {}

/// Getter for the operator
Token ExprNode::getToken() {
    return _tok;
}

/// Abstract accept method for the visitor pattern
int ExprNode::accept(ExprVisitor *visitor) {
    return visitor->evaluate(this);
}

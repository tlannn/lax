#include "exprnode.h"

/// ExprNode constructor
ExprNode::ExprNode(Token tok, Type type) : _tok(tok), _type(type) {}

/// Getter for the operator
Token ExprNode::getToken() {
    return _tok;
}

/// Getter for the type of the expression
Type ExprNode::getType() {
    return _type;
}

int ExprNode::accept(ExprVisitor *visitor) {
    return visitor->evaluate(this);
}

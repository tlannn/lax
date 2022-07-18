#include "exprnode.h"

/// ExprNode constructor
ExprNode::ExprNode(Token *tok) : _tok(tok) {}

/// Getter for the operator
Token* ExprNode::getToken() {
    return _tok;
}

/// Abstract accept method for the visitor pattern
void ExprNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

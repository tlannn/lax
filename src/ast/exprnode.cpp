#include "exprnode.h"

/// Class constructor
ExprNode::ExprNode(Token *token) : _token(token) {}

/// Getter for the token of the node
Token* ExprNode::getToken() {
	return _token;
}

/// Abstract accept method for the visitor pattern
void ExprNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

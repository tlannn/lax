#include "exprnode.h"

/// Class constructor
ExprNode::ExprNode(std::unique_ptr<Token> tok) : _tok(std::move(tok)) {}

/// Getter for the operator
Token* ExprNode::getToken() {
    return _tok.get();
}

/// Abstract accept method for the visitor pattern
void ExprNode::accept(ASTVisitor *visitor) {
	std::cout << "ExprNode - accept" << std::endl;
    visitor->visit(this);
}

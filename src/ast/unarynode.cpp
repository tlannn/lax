#include "unarynode.h"

/// UnaryNode class constructor
UnaryNode::UnaryNode(Token *op, ExprNode *expr) : ExprNode(op), _expr(expr) {}

/// Getter for the expression of the operation
ExprNode *UnaryNode::getExpr() const {
	return _expr;
}

/// Accept method for the visitor pattern
void UnaryNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

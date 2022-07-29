#include "unarynode.h"

/// Class constructor
UnaryNode::UnaryNode(std::unique_ptr<Token> op, std::unique_ptr<ExprNode> expr) :
	ExprNode(op.get()), _op(std::move(op)), _expr(std::move(expr)) {}

/// Getter for the expression of the operation
ExprNode* UnaryNode::getExpr() const {
	return _expr.get();
}

Token* UnaryNode::getOperator() const {
	return _op.get();
}

/// Accept method for the visitor pattern
void UnaryNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

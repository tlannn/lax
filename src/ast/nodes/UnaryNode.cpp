#include "ast/nodes/UnaryNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"
#include "tokens/Token.h"

/// Class constructor
UnaryNode::UnaryNode(UToken op, UExprNode expr) :
	ExprNode(op.get()), _op(std::move(op)), _expr(std::move(expr)) {}

/// Getter for the expression of the operation
ExprNode* UnaryNode::getExpr() const {
	return _expr.get();
}

Token* UnaryNode::getOperator() const {
	return _op.get();
}

/// Accept method for the visitor pattern
void UnaryNode::accept(ASTVisitor &visitor) {
	visitor.visit(*this);
}

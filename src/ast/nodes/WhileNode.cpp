#include "ast/nodes/WhileNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor.
WhileNode::WhileNode(UExprNode cond, UStmtNode body) : StmtNode(),
													   _cond(std::move(cond)), _body(std::move(body)) {}

/// Getter for the expression to evaluate as a condition to continue the loop.
ExprNode* WhileNode::getConditionExpression() {
	return _cond.get();
}

/// Getter for the body of the loop.
StmtNode* WhileNode::getBody() {
	return _body.get();
}

/// Accept method for the visitor pattern.
void WhileNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

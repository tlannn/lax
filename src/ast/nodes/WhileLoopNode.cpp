#include "ast/nodes/WhileLoopNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor.
WhileLoopNode::WhileLoopNode(UExprNode cond, UStmtNode body) : StmtNode(),
															   _cond(std::move(cond)), _body(std::move(body)) {}

/// Getter for the expression to evaluate as a condition to continue the loop.
ExprNode* WhileLoopNode::getConditionExpression() {
	return _cond.get();
}

/// Getter for the body of the loop.
StmtNode* WhileLoopNode::getBody() {
	return _body.get();
}

/// Accept method for the visitor pattern.
void WhileLoopNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

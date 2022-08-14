#include "ast/nodes/ForNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/nodes/BlockNode.h"
#include "ast/nodes/SeqNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor.
ForNode::ForNode(std::vector<UStmtNode> init, UExprNode cond, UExprNode iter, UStmtNode body) : StmtNode(),
	_init(std::move(init)), _cond(std::move(cond)), _iter(std::move(iter)), _body(std::move(body)) {}

/// Getter for the statements in the initialization part of the loop header.
const std::vector<UStmtNode> &ForNode::getInitializers() {
	return _init;
}

/// Getter for the expression to evaluate as a condition to continue the loop.
ExprNode *ForNode::getConditionExpression() {
	return _cond.get();
}

/// Getter for the expression executed after every iteration.
ExprNode *ForNode::getIterationExpression() {
	return _iter.get();
}

/// Getter for the body of the loop.
StmtNode *ForNode::getBody() {
	return _body.get();
}

/// Accept method for the visitor pattern.
void ForNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

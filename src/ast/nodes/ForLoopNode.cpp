#include "ast/nodes/ForLoopNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/nodes/BlockNode.h"
#include "ast/nodes/SeqNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor.
ForLoopNode::ForLoopNode(std::vector<UStmtNode> init, UExprNode cond, UExprNode iter, UStmtNode body) : StmtNode(),
																										_init(std::move(init)), _cond(std::move(cond)), _iter(std::move(iter)), _body(std::move(body)) {}

/// Getter for the statements in the initialization part of the loop header.
const std::vector<UStmtNode> &ForLoopNode::getInitializers() {
	return _init;
}

/// Getter for the expression to evaluate as a condition to continue the loop.
ExprNode *ForLoopNode::getConditionExpression() {
	return _cond.get();
}

/// Getter for the expression executed after every iteration.
ExprNode *ForLoopNode::getIterationExpression() {
	return _iter.get();
}

/// Getter for the body of the loop.
StmtNode *ForLoopNode::getBody() {
	return _body.get();
}

/// Accept method for the visitor pattern.
void ForLoopNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

#include "ast/nodes/CallNode.h"
#include "ast/ASTVisitor.h"
#include "tokens/Token.h"

/// Class constructor
CallNode::CallNode(UExprNode callee, UToken paren,
				   std::vector<UExprNode> args) :
				   ExprNode(callee->getToken()), _callee(std::move(callee)), _paren(std::move(paren)), _args(std::move(args)) {}

/// Getter for the callee
ExprNode* CallNode::getCallee() {
	return _callee.get();
}

/// Getter for the arguments of the call
const std::vector<UExprNode>& CallNode::getArgs() {
	return _args;
}

/// Accept method for the visitor pattern
void CallNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

#include "ast/CallNode.h"

/// Class constructor
CallNode::CallNode(std::unique_ptr<ExprNode> callee, std::unique_ptr<Token> paren,
				   std::vector<std::unique_ptr<ExprNode>> args) :
				   ExprNode(callee->getToken()), _callee(std::move(callee)), _paren(std::move(paren)), _args(std::move(args)) {}

/// Getter for the callee
ExprNode* CallNode::getCallee() {
	return _callee.get();
}

/// Getter for the arguments of the call
const std::vector<std::unique_ptr<ExprNode>>& CallNode::getArgs() {
	return _args;
}

/// Accept method for the visitor pattern
void CallNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

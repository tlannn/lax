#include "ast/ReturnNode.h"

/// Class constructor
ReturnNode::ReturnNode(std::unique_ptr<Token> returnToken, std::unique_ptr<ExprNode> value) :
						StmtNode(), _returnToken(std::move(returnToken)), _value(std::move(value)) {}

/// Getter for the return keyword token
Token* ReturnNode::getToken() {
	return _returnToken.get();
}

/// Getter for the expression returned
ExprNode* ReturnNode::getValue() {
	return _value.get();
}

/// Accept method for the visitor pattern
void ReturnNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

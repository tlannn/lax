#include "ast/nodes/ReturnNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/ASTVisitor.h"
#include "tokens/Token.h"

/// Class constructor
ReturnNode::ReturnNode(UToken returnToken, UExprNode value) :
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

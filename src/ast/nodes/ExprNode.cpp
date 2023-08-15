#include "ast/nodes/ExprNode.h"

#include <utility>
#include "ast/ASTVisitor.h"

/// Class constructor
ExprNode::ExprNode(SToken token) : _token(std::move(token)) {}

/// Getter for the token of the node
Token* ExprNode::getToken() {
	return _token.get();
}

/// Abstract accept method for the visitor pattern
void ExprNode::accept(ASTVisitor &visitor) {
    visitor.visit(*this);
}

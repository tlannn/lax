#include "ast/nodes/LiteralNode.h"
#include "ast/ASTVisitor.h"
#include "tokens/Token.h"

/// Class constructor
LiteralNode::LiteralNode(UToken tok, Value value) :
						ExprNode(tok.get()), _token(std::move(tok)), _value(value) {}

/// Getter for the value of the literal
Value LiteralNode::getValue() {
	return _value;
}

/// Accept method for the visitor pattern
void LiteralNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

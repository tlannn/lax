#include "ast/nodes/IdNode.h"
#include "ast/ASTVisitor.h"
#include "tokens/Token.h"

/// Class constructor
IdNode::IdNode(UToken name) : ExprNode(name.get()), _name(std::move(name)) {}

/// Getter for the name of the identifier
Token *IdNode::getName() {
	return _name.get();
}

/// Accept method for the visitor pattern
void IdNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

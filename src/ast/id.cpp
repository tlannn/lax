#include "id.h"

/// Id constructor
Id::Id(Token *word) : ExprNode(word) {}

/// Accept method for the visitor pattern
void Id::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

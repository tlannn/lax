#include "id.h"

/// Class constructor
Id::Id(std::unique_ptr<Token> word) : ExprNode(std::move(word)) {}

/// Accept method for the visitor pattern
void Id::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

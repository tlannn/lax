#include "id.h"

/// Id constructor
Id::Id(Word word) : ExprNode(word) {}

/// Accept method for the visitor pattern
int Id::accept(ExprVisitor *visitor) {
	return visitor->visit(this);
}

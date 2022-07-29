#include "id.h"

/// Class constructor
Id::Id(std::unique_ptr<Token> name) : ExprNode(name.get()), _name(std::move(name)) {}

/// Getter for the name of the identifier
Token *Id::getName() {
	return _name.get();
}

/// Accept method for the visitor pattern
void Id::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

#include "literalnode.h"

/// Class constructor
LiteralNode::LiteralNode(std::unique_ptr<Token> tok, Type type) : ExprNode(std::move(tok)), _type(type) {}

/// Getter for the value of the literal
Object LiteralNode::getValue() {
	if (_type == Type::INT)
        return Object(stoi(_tok->toString()));
	else if (_type == Type::BOOL)
        return Object(_tok->getType() == TokenType::TRUE);
	else if (_type == Type::STRING)
		return Object(_tok->toString());

    return Object::null;
}

/// Getter for the type of the literal
Type LiteralNode::getType() {
	return _type;
}

/// Accept method for the visitor pattern
void LiteralNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

#include "ast/LiteralNode.h"

/// Class constructor
//LiteralNode::LiteralNode(std::unique_ptr<Token> tok, ValueType type) : ExprNode(std::move(tok)), _type(type) {}
LiteralNode::LiteralNode(std::unique_ptr<Token> tok, Value value) :
						ExprNode(tok.get()), _token(std::move(tok)), _value(value) {}

/// Getter for the value of the literal
Value LiteralNode::getValue() {
	/*if (IS_INT())
	if (_type == ValueType::VAL_INT)
        return Value(stoi(_tok->toString()));
	else if (_type == ValueType::VAL_BOOL)
        return Value(_tok->getType() == TokenType::TRUE);
	else if (_type == ValueType::STRING)
		return Value(_tok->toString());

    return Value::null;*/

	return _value;
}

/// Getter for the type of the literal
Token* LiteralNode::getToken() {
	return _token.get();
}

/// Accept method for the visitor pattern
void LiteralNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

#include "token.h"

/// Token constructor
Token::Token() : _type(TokenType::NONE), _text("") {}

/// Token constructor
Token::Token(TokenType type) : _text(""), _type(type) {}

/// Token constructor
Token::Token(const std::string &lexeme, TokenType type) : _text(lexeme), _type(type) {}

/// Getter for the token type
int Token::getType() const {
    return _type;
}

/// Stringify the token
std::string Token::toString() const {
    return _text;
}

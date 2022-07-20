#include "token.h"

/// Class constructor
Token::Token(const std::string &lexeme, TokenType type, const int line, const int col) :
	_text(lexeme), _type(type), _line(line), _col(col) {}

/// Class constructor
Token::Token(const std::string &lexeme, TokenType type) : Token(lexeme, type, -1, -1) {}

/// Return the lexeme associated to a token type
std::string Token::lexeme(TokenType type) {
	switch (type) {
		// Single character tokens
		case TokenType::LPAREN: return "(";
		case TokenType::RPAREN: return ")";
		case TokenType::LBRACK: return "[";
		case TokenType::RBRACK: return "]";
		case TokenType::LBRACE: return "{";
		case TokenType::RBRACE: return "}";
		case TokenType::SIMEQ: return "=";
		case TokenType::COLON: return ":";
		case TokenType::SEMICOL: return ";";

			// Operators
		case TokenType::BANG: return "!";
		case TokenType::EQ: return "==";
		case TokenType::NEQ: return "!=";
		case TokenType::SL: return "<";
		case TokenType::LE: return "<=";
		case TokenType::SG: return ">";
		case TokenType::GE: return ">=";
		case TokenType::AND: return "&&";
		case TokenType::OR: return "||";

			// Keywords
		case TokenType::VAR: return "var";
		case TokenType::TRUE: return "true";
		case TokenType::FALSE: return "false";
		case TokenType::IF: return "if";
		case TokenType::ELSE: return "else";
		case TokenType::INCLUDE: return "include";
		case TokenType::PRINT: return "print";
		default: return "";
	}
}

/// Getter for the token type
TokenType Token::getType() const {
    return _type;
}

/// Getter for the token line
int Token::getLine() const {
	return _line;
}

/// Getter for the token column
int Token::getColumn() const {
	return _col;
}

/// Stringify the token
std::string Token::toString() const {
    return _text;
}

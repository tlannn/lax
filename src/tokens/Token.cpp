#include "tokens/Token.h"

#include <utility>

Token::Token(std::string lexeme, TokenType type, const int line, const int col) :
    m_text(std::move(lexeme)),
    m_type(type),
    m_line(line),
    m_col(col) {}

Token::Token(const std::string& lexeme, TokenType type) :
    Token(lexeme, type, -1, -1) {}

std::string Token::lexeme(TokenType type) {
    switch (type) {
        // Single character tokens
        case TokenType::LPAREN:     return "(";
        case TokenType::RPAREN:     return ")";
        case TokenType::LBRACK:     return "[";
        case TokenType::RBRACK:     return "]";
        case TokenType::LBRACE:     return "{";
        case TokenType::RBRACE:     return "}";
        case TokenType::SIMEQ:      return "=";
        case TokenType::COLON:      return ":";
        case TokenType::SEMICOL:    return ";";

        // Operators
        case TokenType::BANG:       return "!";
        case TokenType::EQ:         return "==";
        case TokenType::NEQ:        return "!=";
        case TokenType::SL:         return "<";
        case TokenType::LE:         return "<=";
        case TokenType::SG:         return ">";
        case TokenType::GE:         return ">=";
        case TokenType::AND:        return "&&";
        case TokenType::OR:         return "||";

        // Keywords
        case TokenType::VAR:        return "var";
        case TokenType::TRUE:       return "true";
        case TokenType::FALSE:      return "false";
        case TokenType::IF:         return "if";
        case TokenType::ELSE:       return "else";
        case TokenType::INCLUDE:    return "include";
        default:                    return "";
    }
}

TokenType Token::getType() const {
    return m_type;
}

int Token::getLine() const {
    return m_line;
}

int Token::getColumn() const {
    return m_col;
}

std::string Token::toString() const {
    return m_text;
}

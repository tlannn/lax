#include "token.h"

/**
 * Token class definition
 */

/// Token constructor
Token::Token() : _type(TokenType::NONE), _text("") {}

/// Token constructor
Token::Token(TokenType t) : _text(""), _type(t) {}

/// Token constructor
Token::Token(std::string s, TokenType t) : _text(s), _type(t) {}

/// Getter for the token type
int Token::getType() { return _type; }

/// Stringify the token
std::string Token::toString() { return _text; }

/**
 * Num class definition
 */

/// Num constructor
Num::Num(int v) : Token(std::to_string(v), TokenType::NUM) {}

/// Getter for the numeric value of the token
int Num::getValue() { return stoi(_text); }

/// Stringify the token
std::string Num::toString() { return _text; };

/**
 * Op class definition
 */

/// Op constructor
Op::Op(char op) : Token(std::string(1, op), TokenType::OP) {}

/// Stringify the token
std::string Op::toString() { return _text; }

/**
 * Word class definition
 */

/// Word constructor
Word::Word(std::string s, TokenType t) : Token(s, t) {}

/// Stringify the token
std::string Word::toString() { return _text; };

/// Create language-specific words
Word Word::TRUE = Word("true", TokenType::TRUE);
Word Word::FALSE = Word("false", TokenType::FALSE);
Word Word::AND = Word("&&", TokenType::AND);
Word Word::OR = Word("||", TokenType::OR);
Word Word::EQ = Word("==", TokenType::EQ);
Word Word::NEQ = Word("!=", TokenType::NEQ);
Word Word::LE = Word("<=", TokenType::LE);
Word Word::GE = Word(">=", TokenType::GE);
Word Word::IF = Word("if", TokenType::IF);
Word Word::PRINT = Word("print", TokenType::PRINT);

/**
 * Type class definition
 */

/// Type constructor
Type::Type(std::string s, TokenType t, int size) : Word(s, t), _size(size) {}

/// Getter for the type size
int Type::getSize() { return _size; }

/// Overload the equality operator to compare two types
bool operator== (Type &t1, Type &t2) {
    return t1._text == t2._text && t1._type == t2._type && t1._size == t2._size;
}

/// Overload the not equal operator to compare two types
bool operator!= (const Type &t1, const Type &t2) {
    return !(t1._text == t2._text && t1._type == t2._type && t1._size == t2._size);
}

/// Create basic types words
Type Type::INT = Type("int", TokenType::TYPE, 4);
Type Type::BOOL = Type("bool", TokenType::TYPE, 1);

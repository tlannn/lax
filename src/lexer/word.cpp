#include "word.h"

/// Word constructor
Word::Word(const std::string &word, TokenType type) : Token(word, type) {}

/// Stringify the token
std::string Word::toString() const {
    return _text;
};

/// Create language-specific words
Word Word::TRUE = Word("true", TokenType::TRUE);
Word Word::FALSE = Word("false", TokenType::FALSE);
Word Word::AND = Word("&&", TokenType::AND);
Word Word::OR = Word("||", TokenType::OR);
Word Word::EQ = Word("==", TokenType::EQ);
Word Word::NEQ = Word("!=", TokenType::NEQ);
Word Word::SL = Word("<", TokenType::SL);
Word Word::LE = Word("<=", TokenType::LE);
Word Word::SG = Word(">", TokenType::SG);
Word Word::GE = Word(">=", TokenType::GE);
Word Word::IF = Word("if", TokenType::IF);
Word Word::ELSE = Word("else", TokenType::ELSE);
Word Word::PRINT = Word("print", TokenType::PRINT);

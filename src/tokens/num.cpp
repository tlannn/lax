#include "num.h"

/// Num constructor
Num::Num(int value, const int line, const int col) : Token(std::to_string(value), TokenType::NUM, line, col) {}

/// Getter for the numeric value of the token
int Num::getValue() const {
    return stoi(_text);
}

/// Stringify the token
std::string Num::toString() const {
    return _text;
}

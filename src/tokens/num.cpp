#include "num.h"

/// Num constructor
Num::Num(int value) : Token(std::to_string(value), TokenType::NUM) {}

/// Getter for the numeric value of the token
int Num::getValue() const {
    return stoi(_text);
}

/// Stringify the token
std::string Num::toString() const {
    return _text;
}

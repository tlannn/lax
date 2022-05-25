#include "type.h"

/// Type constructor
Type::Type(const std::string &word, TokenType type, int size) : Word(word, type), _size(size) {}

/// Getter for the type size
int Type::getSize() const {
    return _size;
}

/// Overload the equality operator to compare two types
bool operator== (const Type &t1, const Type &t2) {
    return t1._text == t2._text && t1._type == t2._type && t1._size == t2._size;
}

/// Overload the not equal operator to compare two types
bool operator!= (const Type &t1, const Type &t2) {
    return !operator==(t1, t2);
}

/// Create basic types words
Type Type::INT = Type("int", TokenType::TYPE, 4);
Type Type::BOOL = Type("bool", TokenType::TYPE, 1);

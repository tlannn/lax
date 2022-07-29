#include "symbol.h"

/// Class constructor
Symbol::Symbol(std::string name, ValueType type) : _name(std::move(name)), _type(type) {}

/// Getter for the name of the symbol
std::string Symbol::getName() {
    return _name;
}

/// Getter for the type of the symbol
ValueType Symbol::getType() {
    return _type;
}

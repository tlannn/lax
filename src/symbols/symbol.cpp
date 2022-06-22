#include "symbol.h"

/// Class constructor
Symbol::Symbol(std::string name, Type type) : _name(name), _type(type) {}

/// Getter for the name of the symbol
std::string Symbol::getName() {
    return _name;
}

/// Getter for the type of the symbol
Type Symbol::getType() {
    return _type;
}

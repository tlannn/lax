#include "symbols/Symbol.h"

/// Class constructor
Symbol::Symbol(ObjString *name, LaxType *type) : _name(name), _type(type) {}

/// Getter for the name of the symbol
ObjString *Symbol::getName() {
    return _name;
}

/// Getter for the type of the symbol
LaxType* Symbol::getType() {
    return _type;
}

#include "symbols/Symbol.h"

/// Class constructor
Symbol::Symbol(ObjString* name, LaxType* type) :
    m_name(name),
    m_type(type) {}

/// Getter for the name of the symbol
ObjString* Symbol::getName() {
    return m_name;
}

/// Getter for the type of the symbol
LaxType* Symbol::getType() {
    return m_type;
}

#include "symbols/VarSymbol.h"
#include "objects/ObjString.h"

/// Class constructor
VarSymbol::VarSymbol(ObjString* name, LaxType* type) : Symbol(name, type) {}

/// Change the type of the variable
void VarSymbol::setType(LaxType* type) {
    m_type = type;
}

Symbol::Type VarSymbol::getSymbolType() {
    return VARIABLE;
}

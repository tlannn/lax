#include "symbols/VarSymbol.h"
#include "objects/ObjString.h"

VarSymbol::VarSymbol(ObjString* name, LaxType* type) : Symbol(name, type) {}

void VarSymbol::setType(LaxType* type) {
    m_type = type;
}

Symbol::Type VarSymbol::getSymbolType() {
    return VARIABLE;
}

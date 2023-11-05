#include "symbols/BuiltInSymbol.h"

BuiltInSymbol::BuiltInSymbol(ObjString* name, LaxType* type) :
    Symbol(name, type) {}

Symbol::Type BuiltInSymbol::getSymbolType() {
    return BUILTIN;
}

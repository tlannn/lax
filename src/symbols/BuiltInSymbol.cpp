#include "symbols/BuiltInSymbol.h"

/// Class constructor
BuiltInSymbol::BuiltInSymbol(ObjString *name, LaxType *type) :
    Symbol(name, type) {}

Symbol::Type BuiltInSymbol::getSymbolType() {
    return BUILTIN;
}

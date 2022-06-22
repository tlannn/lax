#include "symboltable.h"

/// Class constructor
SymbolTable::SymbolTable() {
	initTypes();
}

/// Initialize built-in types, add all types as symbols in the table
void SymbolTable::initTypes() {
    auto *integer = new Symbol(Type::INT.toString(), Type::INT);
    auto *boolean = new Symbol(Type::BOOL.toString(), Type::BOOL);
    this->define(integer);
    this->define(boolean);
}

/// Add a symbol to the table
void SymbolTable::define(Symbol *symbol) {
    _symbols[symbol->getName()] = symbol;
}

/// Fetch a symbol in the table
Symbol* SymbolTable::lookup(std::string name) {
    if (_symbols.find(name) == _symbols.end()) return nullptr;
    return _symbols[name];
}

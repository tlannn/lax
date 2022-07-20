#include "symboltable.h"

/// Class constructor
SymbolTable::SymbolTable() {
	initTypes();
}

/// Initialize built-in types, add all types as symbols in the table
void SymbolTable::initTypes() {
    auto integer = std::make_unique<Symbol>(Type::INT.toString(), Type::INT);
    auto boolean = std::make_unique<Symbol>(Type::BOOL.toString(), Type::BOOL);
    this->define(std::move(integer));
    this->define(std::move(boolean));
}

/// Add a symbol to the table
void SymbolTable::define(std::unique_ptr<Symbol> symbol) {
    _symbols[symbol->getName()] = std::move(symbol);
}

/// Fetch a symbol in the table
Symbol* SymbolTable::lookup(std::string name) {
    if (_symbols.find(name) == _symbols.end()) return nullptr;
    return _symbols[name].get();
}

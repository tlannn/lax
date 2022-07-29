#include "symboltable.h"

/// Class constructor
SymbolTable::SymbolTable() {
	initTypes();
}

/// Initialize built-in types, add all types as symbols in the table
void SymbolTable::initTypes() {
    auto integer = std::make_unique<Symbol>(ValueType::toString(ValueType::VAL_INT), ValueType::VAL_INT);
    auto boolean = std::make_unique<Symbol>(ValueType::toString(ValueType::VAL_BOOL), ValueType::VAL_BOOL);
    auto string = std::make_unique<Symbol>("string", ValueType::VAL_OBJ);

    this->define(std::move(integer));
    this->define(std::move(boolean));
    this->define(std::move(string));
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

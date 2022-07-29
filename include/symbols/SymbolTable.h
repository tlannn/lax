#ifndef LAX_SYMBOLTABLE_H
#define LAX_SYMBOLTABLE_H

#include <memory>
#include <unordered_map>

#include "Symbol.h"

/**
 * Data structure implement as a hashmap that keeps track of symbols in the
 * program
 */
class SymbolTable {
public:
	/**
	 * Class constructor
	 */
    SymbolTable();

    /**
     * Initialize built-in types, add all types as symbols in the table
     */
    void initTypes();

    /**
     * Add a symbol to the table
     * @param symbol the symbol to add
     */
    void define(std::unique_ptr<Symbol> symbol);

    /**
     * Fetch a symbol in the table
     * @param name the name of the symbol
     * @return the symbol (if found)
     */
    Symbol* lookup(std::string name);

private:
    std::unordered_map<std::string, std::unique_ptr<Symbol>> _symbols;
};


#endif // LAX_SYMBOLTABLE_H

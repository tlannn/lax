#ifndef LAX_ENV_H
#define LAX_ENV_H

#include <string>

#include "symbols/symboltable.h"

/**
 * Represent an environment within a part of the program
 *
 * An environment defines the set of symbols valid and their scope
 */
class Env {
public:
	/**
	 * Default class constructor
	 */
    Env();

	/**
	 * Class constructor
	 *
	 * @param previous
	 */
    explicit Env(Env *previous);

	/**
	 * Define a symbol in the environment
	 *
	 * @param symbol the symbol to add
	 */
    void put(Symbol *symbol);

	/**
	 * Look for a symbol defined in the environment or previous environment
	 *
	 * @param str the symbol name
	 * @return the symbol
	 */
    Symbol* get(std::string str);

	/**
	 * Return the previous environment saved. May be used to go back to a
	 * previous state of the environment
	 *
	 * @return the previous environment
	 */
	Env* getPreviousEnv();

private:
	Env *_previous;
	SymbolTable _table;
};

#endif // LAX_ENV_H

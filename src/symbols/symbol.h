#ifndef LAX_SYMBOL_H
#define LAX_SYMBOL_H

#include <string>

#include "tokens/type.h"

/**
 * Represent an identifier (aka symbol) and carries information with it, that
 * may be its type, its scope, etc.
 */
class Symbol {
public:
	/**
	 * Class constructor
	 *
	 * @param name the name of the symbol
	 * @param type the type of the symbol
	 */
    Symbol(std::string name, Type type);

	/**
	 * Default class destructor
	 */
	virtual ~Symbol() = default;

	/**
	 * Getter for the name of the symbol
	 *
	 * @return the name
	 */
    std::string getName();

	/**
	 * Getter for the type of the symbol
	 *
	 * @return the type
	 */
    Type getType();

protected:
    std::string _name;
    Type _type;
};

#endif // LAX_SYMBOL_H

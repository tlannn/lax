#ifndef LAX_SYMBOL_H
#define LAX_SYMBOL_H

#include <string>

#include "common/valuetype.h"

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
    Symbol(std::string name, ValueType type);

	/**
	 * Class destructor
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
    ValueType getType();

protected:
    std::string _name;
    ValueType _type;
};

#endif // LAX_SYMBOL_H

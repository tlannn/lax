#ifndef LAX_VARSYMBOL_H
#define LAX_VARSYMBOL_H

#include "Symbol.h"

/**
 * Symbol representing a variable
 */
class VarSymbol : public Symbol {
public:
	/**
	 * Class constructor
	 *
	 * @param name the name of the variable
	 * @param type the type of the variable
	 */
    VarSymbol(std::string name, ValueType type);

	/**
	 * Class destructor
	 */
	~VarSymbol() override = default;

	/**
	 * Change the type of the variable
	 * @param type the new type
	 */
	void setType(ValueType type);
};

#endif // LAX_VARSYMBOL_H

#ifndef LAX_VARSYMBOL_H
#define LAX_VARSYMBOL_H

#include "symbol.h"

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
    VarSymbol(std::string &name, Type &type);
};

#endif // LAX_VARSYMBOL_H

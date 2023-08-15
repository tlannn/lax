#ifndef LAX_VARSYMBOL_H
#define LAX_VARSYMBOL_H

#include "Symbol.h"

// Forward declarations
class LaxType;
class ObjString;

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
    VarSymbol(ObjString *name, LaxType *type);

	/**
	 * Change the type of the variable
	 * @param type the new type
	 */
	void setType(LaxType *type);

    Type getSymbolType() override;
};

#endif // LAX_VARSYMBOL_H

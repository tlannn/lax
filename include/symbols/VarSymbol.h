#ifndef LAX_VARSYMBOL_H
#define LAX_VARSYMBOL_H

#include "Symbol.h"

// Forward declarations
class LaxType;
class ObjString;

/**
 * @class VarSymbol
 * @brief Represents a variable symbol in Lax.
 *
 * A variable symbol is a representation of a variable identifier in Lax. It is
 * used to store information about the variable, such as its name and type.
 */
class VarSymbol : public Symbol {
public:
    /**
     * @brief Class constructor.
     * @param name The name of the variable?
     * @param type The type of the variable.
     */
    VarSymbol(ObjString* name, LaxType* type);

    /**
     * @brief Sets the type of the variable.
     *
     * This function sets the type of the variable, which is represented as a
     * Lax type object. This happens when the type of the variable is inferred
     * from the value assigned to it.
     *
     * @param type The type of the variable.
     */
    void setType(LaxType* type);

    /**
     * @copydoc Symbol::getSymbolType()
     */
    Type getSymbolType() override;
};

#endif // LAX_VARSYMBOL_H

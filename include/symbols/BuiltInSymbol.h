#ifndef LAX_BUILTINSYMBOL_H
#define LAX_BUILTINSYMBOL_H

#include <memory>
#include <string>
#include <vector>

#include "Symbol.h"
#include "VarSymbol.h"
#include "values/Value.h"

// Forward declarations
class LaxType;
class ObjString;

/**
 * @class BuiltInSymbol
 * @brief Represents a built-in function symbol in Lax.
 *
 * A built-in function symbol is a representation of a built-in function
 * identifier in Lax. It is used to store information about the function, such
 * as its name, arguments and return type.
 */
class BuiltInSymbol : public Symbol {
public:
    /**
     * @brief Class constructor.
     * @param name The name of the function.
     * @param args The arguments expected by the function.
     * @param returnType The value type returned by the function.
     */
    BuiltInSymbol(ObjString* name, LaxType* type);

    /**
     * @copydoc Symbol::getSymbolType()
     */
    Type getSymbolType() override;
};

#endif // LAX_BUILTINSYMBOL_H

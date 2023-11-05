#ifndef LAX_FUNSYMBOL_H
#define LAX_FUNSYMBOL_H

#define ARGS_TYPE std::vector<VarSymbol>

#include <memory>
#include <string>
#include <vector>

#include "Symbol.h"
#include "VarSymbol.h"

// Forward declarations
class LaxType;
class ObjString;

/**
 * @class FunSymbol
 * @brief Represents a function symbol in Lax.
 *
 * A function symbol is a representation of a function identifier in Lax. It is
 * used to store information about the function, such as its name, arguments and
 * return type.
 */
class FunSymbol : public Symbol {
public:
    /**
     * @brief Class constructor.
     * @param name The name of the function.
     * @param args The arguments expected by the function.
     * @param returnType The type of the value returned by the function.
     */
    FunSymbol(ObjString* name, ARGS_TYPE& args, LaxType* returnType);

    /**
     * @brief Returns the arguments expected by the function.
     *
     * This function returns the arguments expected by the function, which is
     * represented as a vector of variable symbols.
     *
     * @return The arguments expected by the function.
     */
    const ARGS_TYPE& getArgs();

    /**
     * @copydoc Symbol::getSymbolType()
     */
    Type getSymbolType() override;

private:
    ARGS_TYPE m_args;
};

#undef ARGS_TYPE

#endif // LAX_FUNSYMBOL_H

#ifndef LAX_SYMBOL_H
#define LAX_SYMBOL_H

#include <string>

// Forward declarations
class LaxType;
class ObjString;

/**
 * @class Symbol
 * @brief Represents a symbol in Lax.
 *
 * A symbol is a representation of an identifier in Lax. It is used to store
 * information about the identifier, such as its name and type.
 */
class Symbol {
public:
    /**
     * @brief Represents the type of symbol.
     *
     * This enum is used distinguish between different types of symbols, such as
     * built-in functions, variables, etc.
     */
    enum Type {
        BUILTIN,
        VARIABLE,
        FUNCTION
    };

    /**
     * @brief Class constructor.
     * @param name The name of the identifier represented by the symbol.
     * @param type The type of the symbol.
     */
    Symbol(ObjString* name, LaxType* type);

    /**
     * @brief Class destructor.
     */
    virtual ~Symbol() = default;

    /**
     * @brief Returns the name of the identifier represented by the symbol.
     * @return The name of the identifier represented by the symbol.
     */
    ObjString* getName();

    /**
     * @brief Returns the type of value represented by the symbol.
     *
     * This function returns the type of value represented by the symbol, which
     * is represented as a Lax type object.
     *
     * @return The type of value represented by the symbol.
     */
    LaxType* getType();


    /**
     * @brief Returns the type of symbol.
     *
     * This function returns the type of symbol, which can be used to
     * distinguish between different types of symbols, such as built-in
     * functions, variables, etc.
     *
     * @return The type of symbol.
     */
    virtual Type getSymbolType() = 0;

protected:
    ObjString* m_name;
    LaxType* m_type;
};

#endif // LAX_SYMBOL_H

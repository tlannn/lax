#ifndef LAX_SYMBOL_H
#define LAX_SYMBOL_H

#include <string>

// Forward declarations
class LaxType;
class ObjString;

/**
 * Represent an identifier (aka symbol) and carries information with it,
 * that may be its type, its scope, etc.
 * Symbols are used during the semantic analysis of programs.
 */
class Symbol {
public:
    /// Enumeration for the type of symbols.
    enum Type {
        BUILTIN,
        VARIABLE,
        FUNCTION
    };

    /**
     * Class constructor.
     * @param name the name of the identifier represented by the symbol.
     * @param type the type of the symbol
     */
    Symbol(ObjString* name, LaxType* type);

    /**
     * Getter for the name of the identifier represented by the symbol.
     * @return the name of the identifier.
     */
    ObjString* getName();

    /**
     * Getter for the runtime type of the symbol.
     * @return the runtime type.
     */
    LaxType* getType();

    /**
     * Getter for the type of the symbol.
     * @return the type of the symbol.
     */
    virtual Type getSymbolType() = 0;

protected:
    ObjString* m_name;
    LaxType* m_type;
};

#endif // LAX_SYMBOL_H

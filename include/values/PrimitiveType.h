#ifndef LAX_PRIMITIVETYPE_H
#define LAX_PRIMITIVETYPE_H

#include <string>

#include "LaxType.h"

// Forward declarations
class Token;

/**
 * Primitive type in Lax. These types are types natively supported by the
 * language.
 */
class PrimitiveType : public LaxType {
public:
    /// Primitives types instances.
    static PrimitiveType VOID;
    static PrimitiveType BOOLEAN;
    static PrimitiveType INTEGER;
    static PrimitiveType STRING;

    /**
     * Determine the type corresponding to a type keyword.
     * @param token the token representing the type keyword.
     * @return a pointer to the primitive type, or a null pointer if the token
     * doesn't correspond to any type.
     */
    static PrimitiveType* getType(Token* token);

    /**
     * Return the string representation of a primitive type.
     * @param type the type to convert to string.
     * @return the string representation.
     */
    static std::string toString(const PrimitiveType& type);

    /**
     * Return the string representation of the primitive type.
     * @return the string representation.
     */
    std::string toString() const override;

private:
    /// Class constructor.
    PrimitiveType();
};

#endif // LAX_PRIMITIVETYPE_H

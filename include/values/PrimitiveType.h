#ifndef LAX_PRIMITIVETYPE_H
#define LAX_PRIMITIVETYPE_H

#include <string>

#include "LaxType.h"

// Forward declarations
class Token;

/**
 * @class PrimitiveType
 * @brief Class representing the type of a primitive value.
 *
 * This class is used to represent the type of a primitive value in Lax. It is
 * used to distinguish primitive values from other types of values, and to
 * perform type checking.
 */
class PrimitiveType : public LaxType {
public:
    /// Primitives types instances.
    static PrimitiveType VOID;
    static PrimitiveType BOOLEAN;
    static PrimitiveType INTEGER;
    static PrimitiveType STRING;

    /**
     * @brief Determines the type corresponding to a type keyword.
     * @param token The token representing the type keyword.
     * @return A pointer to the primitive type, or nullptr if the token
     * doesn't correspond to any type.
     */
    static PrimitiveType* getType(Token* token);

    /**
     * @brief Returns the string representation of a primitive type.
     * @param type The primitive type to convert.
     * @return The string representation of the primitive type.
     */
    static std::string toString(const PrimitiveType& type);

    /**
     * @copydoc LaxType::toString()
     */
    std::string toString() const override;

private:
    /**
     * @brief Class constructor.
     *
     * Creates a primitive type. This constructor is private to prevent
     * instantiation of primitive types other than the ones defined as static
     * members of this class.
     */
    PrimitiveType();
};

#endif // LAX_PRIMITIVETYPE_H

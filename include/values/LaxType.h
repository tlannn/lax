#ifndef LAX_LAXTYPE_H
#define LAX_LAXTYPE_H

#include <string>

// Forward declarations
class FunctionType;
class ObjectType;
class PrimitiveType;

/**
 * @class LaxType
 * @brief Base class for all types in Lax.
 *
 * This class is used to represent the type of values in Lax. It is used to
 * distinguish different types of values, and to perform type checking.
 */
class LaxType {
public:
    /**
     * @brief Enumeration of all types of values in Lax.
     */
    enum Kind : char {
        PRIMITIVE,
        FUNCTION,
        OBJECT
    };

    /**
     * @brief Class constructor.
     *
     * Creates a type given its kind.
     *
     * @param kind The kind of type to construct.
     */
    explicit LaxType(Kind kind);

    /**
     * @brief Checks whether a type is primitive.
     * @param type The type to check.
     * @return `true` if the type is primitive, `false` otherwise.
     */
    static bool isPrimitive(const LaxType& type);

    /**
     * @brief Converts a type to a primitive type.
     *
     * This function converts a type to a primitive type by down casting it.
     * It is used to avoid the overhead of dynamic casting during runtime.
     *
     * Since no safety check is performed during the conversion, it is advised
     * to check if the type is an actual primitive type.
     *
     * @param type The type to convert.
     * @return The converted type.
     *
     * @see isPrimitive
     */
    static PrimitiveType& asPrimitive(LaxType& type);

    /**
     * @brief Checks whether a type is a function type.
     * @param type The type to check.
     * @return `true` if the type is a function type, `false` otherwise.
     */
    static bool isFunction(const LaxType& type);

    /**
     * @brief Converts a type to a function type.
     *
     * This function converts a type to a function type by down casting it.
     * It is used to avoid the overhead of dynamic casting during runtime.
     *
     * Since no safety check is performed during the conversion, it is advised
     * to check if the type is an actual function type.
     *
     * @param type The type to convert.
     * @return The converted type.
     *
     * @see isFunction
     */
    static FunctionType& asFunction(LaxType& type);

    /**
     * @brief Checks whether a type is an object type.
     * @param type The type to check.
     * @return `true` if the type is an object type, `false` otherwise.
     */
    static bool isObject(const LaxType& type);

    /**
     * @brief Converts a type to an object type.
     *
     * This function converts a type to an object type by down casting it.
     * It is used to avoid the overhead of dynamic casting during runtime.
     *
     * Since no safety check is performed during the conversion, it is advised
     * to check if the type is an actual object type.
     *
     * @param type The type to convert.
     * @return The converted type.
     *
     * @see isObject
     */
    static ObjectType& asObject(LaxType& type);

    /**
     * @brief Returns the kind of the type.
     * @return The kind of the type.
     */
    const Kind& getKind() const;

    /**
     * @brief Returns a string representation of the type.
     * @return A string representation of the type.
     */
    virtual std::string toString() const = 0;

    /**
     * @brief Checks whether two types are equal.
     *
     * This function checks whether two types are equal. It is used to compare
     * types during type checking.
     *
     * @note This function is implemented as a friend function to allow
     * comparing types of different kinds.
     * @param t1 The first type to compare.
     * @param t2 The second type to compare.
     * @return `true` if both types are equal, `false` otherwise.
     */
    friend bool operator==(const LaxType& t1, const LaxType& t2);

    /**
     * @brief Checks whether two types are not equal.
     *
     * This function checks whether two types are not equal. It is used to
     * compare types during type checking.
     *
     * @param t1 The first type to compare.
     * @param t2 The second type to compare.
     * @return `true` if both types are not equal, `false` otherwise.
     */
    friend bool operator!=(const LaxType& t1, const LaxType& t2);

protected:
    /**
     * @brief Checks whether two types are equal.
     *
     * This function checks whether two types are equal. It is used to compare
     * types during type checking.
     *
     * @note This function is implemented as a virtual function to allow
     *       child classes to overload the equality check behavior.
     *
     * @param type The type to compare with.
     * @return `true` if both types are equal, `false` otherwise.
     */
    virtual bool equals(const LaxType& type) const;

private:
    Kind m_kind;
};

#endif // LAX_LAXTYPE_H

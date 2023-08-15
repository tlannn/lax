#ifndef LAX_LAXTYPE_H
#define LAX_LAXTYPE_H

#include <string>

// Forward declarations
class FunctionType;
class ObjectType;
class PrimitiveType;

/**
 * Abstract class for a value type in Lax.
 */
class LaxType {
public:
    /// Enumeration for the kind of values that exists in Lax.
    enum Kind : char {
        PRIMITIVE,
        FUNCTION,
        OBJECT
    };

    /**
     * Class constructor.
     * @param kind the kind of type to construct.
     */
    explicit LaxType(Kind kind);

    /**
     * Check whether a type is primitive.
     * @param type the type to check.
     * @return true if the type is primitive, false otherwise.
     */
    static bool isPrimitive(const LaxType &type);

    /**
     * Convert a type to a primitive type. Since no safety check is performed
     * during the conversion, it is advised to check if the type is an actual
     * primitive type.
     * @param type a reference to the type to convert.
     * @return a reference to converted type.
     */
    static PrimitiveType& asPrimitive(LaxType &type);

    /**
     * Check whether a type is a function type.
     * @param type the type to check.
     * @return true if the type is a function type, false otherwise.
     */
    static bool isFunction(const LaxType &type);

    /**
     * Convert a type to a function type. Since no safety check is performed
     * during the conversion, it is advised to check if the type is an actual
     * function type.
     * @param type a reference to the type to convert.
     * @return a reference to converted type.
     */
    static FunctionType& asFunction(LaxType &type);

    /**
     * Check whether a type is an object type.
     * @param type the type to check.
     * @return true if the type is an object type, false otherwise.
     */
    static bool isObject(const LaxType &type);

    /**
     * Convert a type to an object type. Since no safety check is performed
     * during the conversion, it is advised to check if the type is an actual
     * object type.
     * @param type a reference to the type to convert.
     * @return a reference to converted type.
     */
    static ObjectType& asObject(LaxType &type);

    /**
     * Getter for the kind of type.
     * @return the kind of type.
     */
    const Kind& getKind() const;

    /**
     * Convert the type to a string representation.
     * @return the string representation for this type.
     */
    virtual std::string toString() = 0;

    /**
     * Overload the behavior of the equality operator.
     * @param t1 a reference to the first type to compare.
     * @param t2 a reference the second type to compare.
     * @return true if both types are equal, false otherwise.
     */
    friend bool operator==(const LaxType &t1, const LaxType &t2);

    /**
     * Overload the behavior of the non-equality operator.
     * @param t1 a reference the first type to compare.
     * @param t2 a reference the second type to compare.
     * @return true if both types are not equal, false otherwise.
     */
    friend bool operator!=(const LaxType &t1, const LaxType &t2);

protected:
    /**
     * Check if a type is equal to a type instance.
     * @param type a reference to the type to compare.
     * @return true if the compared type is equal, false otherwise.
     */
    virtual bool equals(const LaxType &type) const;

private:
    Kind m_kind;
};

#endif // LAX_LAXTYPE_H

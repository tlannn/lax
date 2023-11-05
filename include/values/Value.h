#ifndef LAX_VALUE_H
#define LAX_VALUE_H

#include <memory>
#include <utility>
#include <vector>

#include "common/Memory.h"

// Forward declarations
class LaxType;
class FunctionType;
class ObjectType;
class Object;
class ObjFunction;

/**
 * @brief Enumeration of all types of values in Lax.
 */
enum ValueType {
    NUL,
    INTEGER,
    BOOLEAN,
    FUNCTION,
    OBJECT
};

#define AS_BOOL(value)       ((value).as.b)
#define AS_INT(value)        ((value).as.i)
#define AS_OBJ(value)        ((value).as.obj)

#define IS_BOOL(value)       ((value).type == ValueType::BOOLEAN)
#define IS_INT(value)        ((value).type == ValueType::INTEGER)
#define IS_OBJ(value)        ((value).type == ValueType::OBJECT)
#define IS_NULL(value)       ((value).type == ValueType::NUL)

/**
 * @class Value
 * @brief Class representing a value in Lax.
 *
 * This class is used to represent a value in Lax. It is used to distinguish
 * values from other types of objects, and to perform type checking.
 */
struct Value {
    ValueType type;
    union value {
        bool b;
        int i;
        Object* obj;
    } as;

    /**
     * @brief Class constructor.
     *
     * Constructs a null value.
     */
    Value();

    /**
     * @brief Constructs a null value.
     * @return A null value.
     */
    static Value null();

    /**
     * @brief Constructs a function value.
     * @param function The function to treat as a value.
     * @return The function as a value.
     */
    static Value function(ObjFunction* function);

    /**
     * @brief Constructs an object value.
     * @param object The object to treat as a value.
     * @return The object as a value.
     */
    static Value object(Object* object);

    /**
     * @brief Constructs a boolean value.
     * @param b The boolean to treat as a value.
     * @return The boolean as a value.
     */
    static Value boolean(bool b);

    /**
     * @brief Constructs an integer value.
     * @param i The integer to treat as a value.
     * @return The integer as a value.
     */
    static Value integer(int i);

    /**
     * @brief Checks whether a value is considered false in Lax.
     * @param value The value to check.
     * @return `true` if the value is considered false, `false` otherwise.
     */
    static bool isFalsy(Value value);

    /**
     * @brief Checks if two values are considered equal in Lax.
     * @param a The first value to check.
     * @param b The second value to check.
     * @return `true` if both values are considered equal, `false` otherwise.
     */
    static bool equals(Value a, Value b);

    /**
     * @brief Returns the string representation of a value.
     * @param value The value to represent as a string.
     * @return The string representation of the value.
     */
    static std::string toString(Value& value);

    /**
     * @brief Assigns a value to this object.
     * @param value The value to assign.
     * @return A reference to this object.
     */
    Value& operator=(const Value& value);

private:
    /**
     * @brief Class constructor.
     *
     * Constructs a value given its type and representation.
     *
     * @param type The type of value.
     * @param v The actual value representation.
     */
    Value(ValueType type, union value v);

    /**
     * @brief Class constructor.
     *
     * Constructs a value given its type and a pointer to the object to treat as
     * a value.
     *
     * @param type The type of value.
     * @param object The object to treat as a value.
     */
    Value(ValueType type, Object* object);
};

#endif // LAX_VALUE_H

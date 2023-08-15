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

/// Enumeration of the types of values that can be represented as a Value object.
enum ValueType {
    NUL,
    INTEGER,
    BOOLEAN,
    FUNCTION,
    OBJECT
};

#define AS_BOOL(value)		((value).as.b)
#define AS_INT(value)		((value).as.i)
#define AS_OBJ(value)		((value).as.obj)

#define IS_BOOL(value)		((value).type == ValueType::BOOLEAN)
#define IS_INT(value)		((value).type == ValueType::INTEGER)
#define IS_OBJ(value)		((value).type == ValueType::OBJECT)
#define IS_NULL(value)		((value).type == ValueType::NUL)

/**
 * Value in Lax, be it of a primitive type or an object.
 */
struct Value {
    ValueType type;
    union value {
        bool b;
        int i;
        Object *obj;
    } as;

    /// Class constructor.
    Value();

    /**
     * Construct a null value.
     * @return a null value.
     */
    static Value null();

    /**
     * Construct a function value.
     * @param function a pointer to the object representing the function.
     * @return the function as a value.
     */
    static Value function(ObjFunction *function);

    /**
     * Construct an object value.
     * @param object a pointer to the object.
     * @return the object as a value.
     */
    static Value object(Object *object);

    /**
     * Construct a boolean value.
     * @param b the boolean value.
     * @return the boolean as a value.
     */
    static Value boolean(bool b);

    /**
     * Construct an integer value.
     * @param i the integer.
     * @return
     */
    static Value integer(int i);

	/**
	 * Check if a value is considered false in Lax.
	 * @param value the value to check.
	 * @return true if the value is considered false.
	 */
	static bool isFalsy(Value value);

	/**
	 * Check if two values are considered equal in Lax.
	 * @param a the first value to check.
	 * @param b the second value to check.
	 * @return true if the two values are considered equal.
	 */
	static bool equals(Value a, Value b);

	/**
	 * Return the string representation of a value.
	 * @param value the value to represent as a string.
	 * @return the string representation.
	 */
	static std::string toString(Value &value);

    /**
     * Overload the behavior of the assign operator.
     * @param value the value to assign to this object.
     * @return the assigned object.
     */
    Value& operator=(const Value &value);

private:
    /**
     * Class constructor.
     * @param type the type of value.
     * @param v the actual value representation.
     */
    Value(ValueType type, union value v);

    /**
     * Class constructor.
     * @param type the type of value.
     * @param object a pointer to the object to treat as a value.
     */
    Value(ValueType type, Object *object);
};

#endif // LAX_VALUE_H

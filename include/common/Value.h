#ifndef LAX_VALUE_H
#define LAX_VALUE_H

#include <memory>

#include "Memory.h"
#include "ValueType.h"

// Forward declarations
class Object;

#define NULL_VAL			((Value){ValueType::VAL_NULL, {.i = 0}})
#define BOOL_VAL(value)		((Value){ValueType::VAL_BOOL, {.b = (value)}})
#define INT_VAL(value)		((Value){ValueType::VAL_INT, {.i = (value)}})
#define OBJ_VAL(object)		((Value){ValueType::VAL_OBJ, {.obj = static_cast<Object*>(object)}})

#define AS_BOOL(value)		((value).as.b)
#define AS_INT(value)		((value).as.i)
#define AS_OBJ(value)		((value).as.obj)

#define IS_BOOL(value)		((value).type == ValueType::VAL_BOOL)
#define IS_NULL(value)		((value).type == ValueType::VAL_NULL)
#define IS_INT(value)		((value).type == ValueType::VAL_INT)
#define IS_OBJ(value)		((value).type == ValueType::VAL_OBJ)

/**
 * Value in Lax, be it of a primitive type or an object.
 */
typedef struct Value {
	ValueType type;
	union value {
		bool b;
		int i;
		Object* obj;
	} as;

	/// Structure constructor.
	Value() : type(ValueType::VAL_NULL), as({.i = 0}) {}

	/**
	 * Structure constructor.
	 *
	 * @param type the type of the value.
	 * @param value the actual value.
	 */
	Value(ValueType type, union value value) : type(type), as(value) {}

	/**
	 * Check if a value is considered false in Lax.
	 *
	 * @param value the value to check.
	 * @return true if the value is considered false.
	 */
	static bool isFalsy(Value value);

	/**
	 * Check if two values are considered equal in Lax.
	 *
	 * @param a the first value to check.
	 * @param b the second value to check.
	 * @return true if the two values are considered equal.
	 */
	static bool equals(Value a, Value b);

	/**
	 * Return the string representation of a value.
	 *
	 * @param value the value to represent as a string.
	 * @return the string representation.
	 */
	static std::string toString(Value &value);
} Value;

/**
 * Array of values.
 */
class ValueArray {
public:
	/// Class constructor.
	ValueArray();

	/// Class destructor.
	~ValueArray();

	/**
	 * Append a value to the array.
	 * @param value the value to add.
	 */
	void writeValue(Value value);

	/**
	 * Getter for the number of values in the array.
	 * @return the number of values.
	 */
	int getCount() const;

	/**
	 * Return a value from the array.
	 *
	 * @param offset the offset of the value in the array.
	 * @return the value.
	 */
	const Value& getValue(int offset);

private:
	int _count;
	int _capacity;
	Value *_values;
};

#endif // LAX_VALUE_H

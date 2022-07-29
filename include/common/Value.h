#ifndef LAX_VALUE_H
#define LAX_VALUE_H

#include <memory>

#include "ValueType.h"

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
 * Structure representing a value in Lax, be it of a primitive type or an object
 */
typedef struct Value {
	ValueType type;
	union value {
		bool b;
		int i;
		Object* obj;
	} as;

	/**
	 * Structure constructor
	 */
	Value() : type(ValueType::VAL_NULL), as({.i = 0}) {}

	/**
	 * Structure constructor
	 * @param type the type of the value
	 * @param value the actual value
	 */
	Value(ValueType type, union value value) : type(type), as(value) {}
} Value;

#endif // LAX_VALUE_H

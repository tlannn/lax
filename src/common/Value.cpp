#include "common/Value.h"
#include "objects/Object.h"

/// Class constructor.
ValueArray::ValueArray() : _count(0), _capacity(0), _values(nullptr) {}

/// Class destructor.
ValueArray::~ValueArray() {
	FREE_ARRAY(Value, _values, _capacity);
}

/// Append a value to the array.
void ValueArray::writeValue(Value value) {
	if (_capacity < _count + 1) {
		int oldCapacity = _capacity;
		_capacity = GROW_CAPACITY(oldCapacity);
		_values = GROW_ARRAY(Value, _values, oldCapacity, _capacity);
	}

	_values[_count] = value;
	++_count;
}

/// Getter for the number of values in the array.
int ValueArray::getCount() const {
	return _count;
}

/// Return a value from the array.
const Value& ValueArray::getValue(int offset) {
	return _values[offset];
}

/// Check if a value is considered false in Lax.
bool Value::isFalsy(Value value) {
	return IS_NULL(value) || (IS_INT(value) && AS_INT(value) == 0) || (IS_BOOL(value) && !AS_BOOL(value));
}

/// Check if two values are considered equal in Lax.
bool Value::equals(Value a, Value b) {
	if (a.type != b.type) return false;

	switch (a.type) {
		case ValueType::VAL_NULL:	return true;
		case ValueType::VAL_BOOL:	return AS_BOOL(a) == AS_BOOL(b);
		case ValueType::VAL_INT:	return AS_INT(a) == AS_INT(b);
		case ValueType::VAL_OBJ:	return AS_OBJ(a) == AS_OBJ(b);
		default:					return false;
	}
}

/// Return the string representation of a value.
std::string Value::toString(Value &value) {
	switch (value.type) {
		case ValueType::VAL_NULL: 	return "null";
		case ValueType::VAL_INT: 	return std::to_string(AS_INT(value));
		case ValueType::VAL_BOOL: 	return AS_BOOL(value) ? "true" : "false";
		case ValueType::VAL_OBJ: 	return AS_OBJ(value)->toString();
	}
}

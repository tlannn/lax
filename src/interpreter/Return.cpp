#include "interpreter/Return.h"

/// Class constructor
Return::Return(Value value) : Exception("", ""), _value(std::move(value)) {}

/// Getter for the value returned
Value Return::getValue() {
	return _value;
}

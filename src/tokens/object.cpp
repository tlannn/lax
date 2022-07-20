#include "object.h"
#include "interpreter/runtimeerror.h"

Object Object::null = Object();

/// Class constructor
Object::Object() : _type(Type::NONE), _value() {}

/// Class constructor
Object::Object(int i) : _type(Type::INT), _value() {
	_value.i = i;
}

/// Class constructor
Object::Object(bool b) : _type(Type::BOOL), _value() {
	_value.b = b;
}

/// Class constructor
Object::Object(std::string s) : _type(Type::STRING), _value(), _stringValue(s) {}

/// Return for the integer representation of the object
int Object::toInt() const {
	if (_type == Type::INT)
		return _value.i;
	else if (_type == Type::BOOL)
		return _value.b;
	else return 0;
}

/// Return for the boolean representation of the object
bool Object::toBool() const {
	if (_type == Type::BOOL)
		return _value.b;
	else if (_type == Type::NONE)
		return false;
	else return true;
}

/// Return for the string representation of the object
std::string Object::toString() const {
	if (_type == Type::STRING)
		return _stringValue;
	else if (_type == Type::INT)
		return std::to_string(_value.i);
	else if (_type == Type::BOOL)
		return _value.b ? "true" : "false";
	else if (_type == Type::NONE)
		return "null";
	else return "";
}

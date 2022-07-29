#include "objstring.h"

/// Class constructor
ObjString::ObjString() : Object(ObjType::OBJ_STRING), _length(0) {}

/// Class constructor
ObjString::ObjString(std::string chars) : Object(ObjType::OBJ_STRING), _length(chars.size()), _chars(std::move(chars)) {}

/// Getter for the length of the string
int ObjString::getLength() {
	return _length;
}

std::string ObjString::toString() {
	return _chars;
}

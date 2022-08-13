#include "objects/Object.h"

/// Class constructor.
Object::Object(ObjType type) : _type(type) {}

/// Class destructor.
Object::~Object() = default;

/// Return the type of the object.
ObjType Object::getType() {
	return _type;
}

/// Return a string representation of the object.
std::string Object::toString() {
	return "<obj>";
}

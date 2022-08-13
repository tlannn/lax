#include "objects/ObjNative.h"

/// Class constructor
ObjNative::ObjNative(NativeFn function) : Object(ObjType::OBJ_NATIVE), _function(function) {}

/// Getter for the pointer to the native function
NativeFn ObjNative::getFunction() {
	return _function;
}

/// Return a string representation of the object
std::string ObjNative::toString() {
	return "<native fn>";
}

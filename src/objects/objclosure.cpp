#include "objclosure.h"
#include "objfunction.h"

/// Class constructor
ObjClosure::ObjClosure(ObjFunction *function) : Object(ObjType::OBJ_CLOSURE), _function(function) {}

/// Getter for the function referenced
ObjFunction *ObjClosure::getFunction() {
	return _function;
}

/// Return a string representation of the function
std::string ObjClosure::toString() {
	return _function->toString();
}

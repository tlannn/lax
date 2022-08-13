#include "objects/ObjClosure.h"
#include "objects/ObjFunction.h"

/// Class constructor.
ObjClosure::ObjClosure(ObjFunction *function) : Object(ObjType::OBJ_CLOSURE), _function(function),
	_upvalueCount(function->getUpvalueCount()) {
	_upvalues = new ObjUpvalue*[_upvalueCount];

	// Initialize for garbage collector
	for (int i = 0; i < _upvalueCount; ++i)
		_upvalues[i] = nullptr;
}

/// Getter for the function referenced.
ObjFunction *ObjClosure::getFunction() {
	return _function;
}

/// Getter for the upvalues captured by the closure.
ObjUpvalue **ObjClosure::getUpvalues() const {
	return _upvalues;
}

/// Return the number of upvalues captured by the closure.
int ObjClosure::getUpvalueCount() const {
	return _upvalueCount;
}

/// Return a string representation of the closure.
std::string ObjClosure::toString() {
	return _function->toString();
}

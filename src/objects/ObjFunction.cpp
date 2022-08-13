#include "objects/ObjFunction.h"
#include "objects/ObjString.h"

/// Class constructor.
ObjFunction::ObjFunction(ObjString *name, int arity) : Object(ObjType::OBJ_FUNCTION), _name(name), _arity(arity),
	_upvalueCount(0) {}

/// Getter for the number of parameters of the function.
int ObjFunction::arity() const {
	return _arity;
}

/// Increment the number of upvalues used in the function.
void ObjFunction::incrementUpvalueCount() {
	_upvalueCount++;
}

/// Return the number of upvalues used in the function.
int ObjFunction::getUpvalueCount() const {
	return _upvalueCount;
}

/// Return a pointer to the chunk of bytecode that depicts the function.
Chunk* ObjFunction::getChunk() {
	return &_chunk;
}

/// Return a string representation of the function.
std::string ObjFunction::toString() {
	return _name ? "<fn " + _name->toString() + ">" : "<script>";
}

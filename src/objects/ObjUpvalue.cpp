#include "objects/ObjUpvalue.h"

ObjUpvalue::ObjUpvalue(Value *slot) : Object(ObjType::OBJ_UPVALUE), _location(slot), _closed(NULL_VAL),
									  _next(nullptr) {}

Value* ObjUpvalue::getLocation() const {
	return _location;
}

ObjUpvalue* ObjUpvalue::getNext() const {
	return _next;
}

void ObjUpvalue::setNext(ObjUpvalue *nextUpvalue) {
	_next = nextUpvalue;
}

void ObjUpvalue::setClosed(Value value) {
	_closed = value;
	_location = &_closed;
}

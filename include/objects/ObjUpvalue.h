#ifndef LAX_OBJUPVALUE_H
#define LAX_OBJUPVALUE_H

#include "common/Value.h"
#include "objects/Object.h"

/**
 * Upvalue object in Lax
 *
 * An upvalue refers to a local variable in an enclosing function. Its purpose
 * is to keep track of a local variable that may go out of scope, but is needed
 * for later use.
 *
 * An upvalue first points back into the stack where the variable it captured
 * lives. If the captured variable goes out of scope and moves off the stack,
 * then the upvalue copies its value, so it can continue to find it.
 */
class ObjUpvalue : public Object {
public:
	explicit ObjUpvalue(Value *slot);

	Value* getLocation() const;

	ObjUpvalue* getNext() const;

	void setNext(ObjUpvalue *nextUpvalue);

	void setClosed(Value value);

private:
	Value *_location;
	Value _closed;
	ObjUpvalue *_next;
};

#endif //LAX_OBJUPVALUE_H

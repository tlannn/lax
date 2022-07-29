#ifndef LAX_OBJCLOSURE_H
#define LAX_OBJCLOSURE_H

#include "object.h"

class ObjFunction;

/**
 * Closure object in Lax
 *
 * A closure is an overlay to function objects. It tracks non-local variables
 * used in functions in a separate environment, so that the function still have
 * access to these variables even if they go out of the scope where the
 * function is called
 */
class ObjClosure : public Object {
public:
	/**
	 * Class constructor
	 * @param function the function object that the closure references
	 */
	explicit ObjClosure(ObjFunction *function);

	/**
	 * Getter for the function referenced
	 * @return the function referenced
	 */
	ObjFunction* getFunction();

	/**
	 * Return a string representation of the closure
	 */
	std::string toString() override;

private:
	ObjFunction *_function;
};

#define AS_CLOSURE(value)	((dynamic_cast<ObjClosure*>(AS_OBJ(value))))

#endif // LAX_OBJCLOSURE_H

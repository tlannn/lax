#ifndef LAX_CALLABLE_H
#define LAX_CALLABLE_H

#include <vector>

#include "values/Value.h"
#include "vm/VM.h"

class Interpreter;

/**
 * Interface representing a callable object in Lax
 */
class Callable {
public:
	/**
	 * Return the arity of the callable
	 * @return the arity
	 */
	virtual int arity() = 0;

	/**
	 * Execute a call of the callable
	 * @param interpreter the interpreter executing the call
	 * @param frame the call frame where the call occur
	 * @param args the arguments passed to the call
	 * @return the value resulting after the call
	 */
	virtual Value call(Interpreter *interpreter, CallFrame *frame, std::vector<Value> args) = 0;
};

#endif //LAX_CALLABLE_H

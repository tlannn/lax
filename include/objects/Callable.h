#ifndef LAX_CALLABLE_H
#define LAX_CALLABLE_H

#include <vector>

#include "values/Value.h"
#include "vm/VM.h"

class Interpreter;

/**
 * @interface Callable
 * @brief Interface for all callable objects in Lax.
 *
 * This interface is used to represent callable objects in Lax. It is used to
 * distinguish different types of callable objects, and to perform type checking.
 *
 * A callable object is an object that can be called, i.e. that can be used as a
 * function. It can be a function, a method, or a class.
 */
class Callable {
public:
    /**
     * @brief Returns the arity of the callable.
     *
     * The arity of a callable is the number of arguments it takes.
     *
     * @return The arity of the callable.
     */
    virtual int arity() = 0;

    /**
     * @brief Calls the callable object.
     *
     * This function is used to call the callable object. It is called by the
     * interpreter when a call expression is evaluated.
     *
     * @param interpreter The interpreter that is executing the call.
     * @param frame The call frame in which the call is executed.
     * @param args The arguments passed to the call.
     * @return The value returned by the call.
     */
    virtual Value call(Interpreter* interpreter, CallFrame* frame,
        std::vector<Value> args) = 0;
};

#endif //LAX_CALLABLE_H

#ifndef LAX_OBJCLOSURE_H
#define LAX_OBJCLOSURE_H

#include "objects/Object.h"

// Forward declarations
class ObjFunction;
class ObjUpvalue;

/**
 * @class ObjClosure
 * @brief Closure object in Lax.
 *
 * A closure is an overlay to function objects. It bundles a function with its
 * lexical environment, which is the set of variables in the surrounding scopes
 * that are used in the function. These variables are called upvalues.
 *
 * By keeping track of the upvalues, the closure allows the function to access
 * variables that are not in its scope, even when the said variables go out of
 * scope.
 *
 * The closure is implemented as a linked list of upvalues. The upvalues are
 * ordered by stack index, which makes it easy to close all upvalues above a
 * certain index when a function returns.
 *
 * When a function is called, a new closure is created. When the function
 * returns, the closure is destroyed.
 *
 * The closure is stored in the stack frame of the function. When the function
 * returns, the closure is popped from the stack frame.
 *
 * @see ObjFunction
 */
class ObjClosure : public Object {
public:
    /**
     * @brief Class constructor.
     *
     * Construct a closure object that references a function.
     *
     * @param function The function referenced.
     */
    explicit ObjClosure(ObjFunction* function);

    /**
     * @brief Retrieves the function referenced.
     * @return The function referenced.
     */
    ObjFunction* getFunction();

    /**
     * @brief Returns the upvalues captured by the closure.
     *
     * The upvalues are provided as a linked list.
     *
     * @return The upvalues used in the function.
     */
    ObjUpvalue** getUpvalues() const;

    /**
     * @brief Returns the number of upvalues captured by the closure.
     * @return The number of upvalues captured.
     */
    int getUpvalueCount() const;

    /**
     * @copydoc Object::toString()
     */
    std::string toString() override;

private:
    ObjFunction* m_function;
    ObjUpvalue** m_upvalues;
    int m_upvalueCount;
};

#define AS_CLOSURE(value)    ((dynamic_cast<ObjClosure*>(AS_OBJ(value))))

#endif // LAX_OBJCLOSURE_H

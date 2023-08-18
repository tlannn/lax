#ifndef LAX_OBJCLOSURE_H
#define LAX_OBJCLOSURE_H

#include "objects/Object.h"

// Forward declarations
class ObjFunction;
class ObjUpvalue;

/**
 * Closure object in Lax.
 *
 * A closure is an overlay to function objects. It tracks non-local variables
 * called upvalues used in the function, but that belong to surrounding scopes.
 * Thus these variables can always be used in the function, even if they go
 * out of scope.
 */
class ObjClosure : public Object {
public:
    /**
     * Class constructor.
     *
     * @param function the function object that the closure references.
     */
    explicit ObjClosure(ObjFunction* function);

    /**
     * Getter for the function referenced.
     *
     * @return the function referenced.
     */
    ObjFunction* getFunction();

    /**
     * Getter for the upvalues captured by the closure.
     *
     * @return the upvalues used in the function.
     */
    ObjUpvalue** getUpvalues() const;

    /**
     * Return the number of upvalues captured by the closure.
     *
     * @return the number of upvalues captured.
     */
    int getUpvalueCount() const;

    /// Return a string representation of the closure.
    std::string toString() override;

private:
    ObjFunction* m_function;
    ObjUpvalue** m_upvalues;
    int m_upvalueCount;
};

#define AS_CLOSURE(value)    ((dynamic_cast<ObjClosure*>(AS_OBJ(value))))

#endif // LAX_OBJCLOSURE_H

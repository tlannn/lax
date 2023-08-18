#ifndef LAX_OBJNATIVE_H
#define LAX_OBJNATIVE_H

#include <string>

#include "objects/Object.h"
#include "values/Value.h"

/// Type for native functions.
typedef Value (*NativeFn)(int argCount, Value* args);

/**
 * Native function object in Lax.
 *
 * Native functions are functions implemented natively, as opposed to
 * user-defined functions.
 */
class ObjNative : public Object {
public:
    /**
     * Class constructor.
     *
     * @param function the pointer to the native function that the object wraps.
     */
    explicit ObjNative(NativeFn function);

    /**
     * Getter for the pointer to the native function.
     *
     * @return the pointer to the native function.
     */
    NativeFn getFunction();

    /// Return a string representation of the object.
    std::string toString() override;

private:
    NativeFn m_function;
};

#define AS_NATIVE(value) \
    ((dynamic_cast<ObjNative*>(AS_OBJ(value))->getFunction()))

#endif //LAX_OBJNATIVE_H

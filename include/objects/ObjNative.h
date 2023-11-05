#ifndef LAX_OBJNATIVE_H
#define LAX_OBJNATIVE_H

#include <string>

#include "objects/Object.h"
#include "values/Value.h"

/**
 * @typedef NativeFn
 * @brief Native function type in Lax.
 */
typedef Value (*NativeFn)(int argCount, Value* args);

/**
 * @class ObjNative
 * @brief Native function object in Lax.
 *
 * Native functions are functions implemented natively, as opposed to
 * user-defined functions.
 *
 * @see ObjFunction
 */
class ObjNative : public Object {
public:
    /**
     * @brief Class constructor.
     *
     * Constructs a native function object that wraps a native function.
     *
     * @param function The native function to wrap.
     */
    explicit ObjNative(NativeFn function);

    /**
     * @brief Returns the native function wrapped.
     * @return The native function.
     */
    NativeFn getFunction();

    /**
     * @copydoc Object::toString()
     */
    std::string toString() override;

private:
    NativeFn m_function;
};

#define AS_NATIVE(value) \
    ((dynamic_cast<ObjNative*>(AS_OBJ(value))->getFunction()))

#endif //LAX_OBJNATIVE_H

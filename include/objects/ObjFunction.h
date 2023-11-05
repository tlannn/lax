#ifndef LAX_OBJFUNCTION_H
#define LAX_OBJFUNCTION_H

#include <memory>
#include <string>
#include <vector>

#include "common/Chunk.h"
#include "objects/Object.h"

// Forward declarations
class ObjString;

/**
 * @class ObjFunction
 * @brief Function object in Lax.
 *
 * A function is an object that can be called. It is defined by a sequence of
 * instructions, called bytecode. The bytecode is stored in a chunk.
 *
 * A function can be called with a number of arguments. These arguments are
 * stored in a stack. The function can also access variables defined in the
 * surrounding scopes. These variables are stored in a stack called the
 * upvalue stack.
 *
 * When a function is called, a new stack frame is created. It contains the
 * arguments and the upvalues. The stack frame is pushed on the call stack.
 *
 * When the function returns, the stack frame is popped from the call stack.
 *
 * The function can return a value. This value is stored in the stack of the
 * calling function.
 */
class ObjFunction : public Object {
public:
    /**
     * @brief Class constructor.
     *
     * Constructs a function object with a name and a number of parameters,
     * which is called the arity of the function and is used to check the number
     * of arguments passed to the function.
     *
     * @param name The name of the function.
     * @param arity (optional) The number of parameters of the function.
     */
    explicit ObjFunction(ObjString* name, int arity = 0);

    /**
     * @brief Returns the arity of the function.
     *
     * The arity of a function is the number of parameters it takes.
     *
     * @return The arity of the function.
     */
    int arity() const;

    /**
     * @brief Increments the number of upvalues used in the function.
     *
     * This function is used when a new upvalue is created in the function.
     */
    void incrementUpvalueCount();

    /**
     * @brief Returns the number of upvalues used in the function.
     * @return The number of upvalues used.
     */
    int getUpvalueCount() const;

    /**
     * @brief Retrieves the chunk of bytecode of the function.
     * @return The chunk of bytecode of the function.
     */
    Chunk* getChunk();

    /**
     * @copydoc Object::toString()
     */
    std::string toString() override;

private:
    ObjString* m_name;
    int m_arity;
    int m_upvalueCount;
    Chunk m_chunk;
};

#define AS_FUNCTION(value)    ((dynamic_cast<ObjFunction*>(AS_OBJ(value))))

#endif // LAX_OBJFUNCTION_H

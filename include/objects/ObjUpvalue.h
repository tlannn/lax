#ifndef LAX_OBJUPVALUE_H
#define LAX_OBJUPVALUE_H

#include "objects/Object.h"
#include "values/Value.h"

/**
 * @class ObjUpvalue
 * @brief Upvalue object in Lax.
 *
 * An upvalue refers to a local variable in an enclosing function. Its purpose
 * is to keep track of a local variable that may go out of scope, but is needed
 * for later use.
 *
 * An upvalue first points back into the stack where the variable it captured
 * lives. If the captured variable goes out of scope and moves off the stack,
 * then the upvalue copies its value, so it can continue to find it.
 *
 * An upvalue can be closed, which means that it has been copied out of the
 * stack and into the upvalue itself. This is done when the function that
 * created the upvalue returns.
 *
 * Upvalues are stored in a linked list, ordered by stack index. This makes it
 * easy to close all upvalues above a certain index when a function returns.
 *
 * Upvalues are created when a function is called. When the function returns,
 * all upvalues are closed.
 */
class ObjUpvalue : public Object {
public:
    /**
     * @brief Class constructor.
     *
     * Constructs an upvalue object that points to a value in the stack.
     *
     * @param slot A pointer to the value in the stack.
     */
    explicit ObjUpvalue(Value* slot);

    /**
     * @brief Retrieves the location of the upvalue.
     *
     * The location of the upvalue is the slot in the stack where the value
     * pointed to is stored.
     *
     * @return A pointer to the value in the stack.
     */
    Value* getLocation() const;

    /**
     * @brief Returns the next upvalue in the list.
     *
     * The next upvalue in the list is the upvalue that is above the current
     * upvalue in the stack.
     *
     * @return A pointer to The next upvalue in the list.
     */
    ObjUpvalue* getNext() const;

    /**
     * @brief Defines the next upvalue in the list.
     *
     * The next upvalue in the list is the upvalue that is above the current
     * upvalue in the stack.
     *
     * @param nextUpvalue A pointer to the next upvalue in the list.
     */
    void setNext(ObjUpvalue* nextUpvalue);

    /**
     * @brief Closes the upvalue.
     *
     * Closing an upvalue means that the value pointed to by the upvalue is
     * copied into the upvalue itself. This is done when the function that
     * created the upvalue returns, so that the upvalue can continue to find
     * the value even after the function has returned.
     *
     * @param value The value to close the upvalue with.
     */
    void setClosed(Value value);

private:
    Value* m_location;
    Value m_closed;
    ObjUpvalue* m_next;
};

#endif //LAX_OBJUPVALUE_H

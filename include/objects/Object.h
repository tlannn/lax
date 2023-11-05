#ifndef LAX_OBJECT_H
#define LAX_OBJECT_H

#include <string>

#include "values/Value.h"

#define OBJ_TYPE(value)         (AS_OBJ(value)->getType())

#define IS_STRING(value)        Object::isObjType(value, OBJ_STRING)
#define IS_UPVALUE(value)       Object::isObjType(value, OBJ_UPVALUE)
#define IS_FUNCTION(value)      Object::isObjType(value, OBJ_FUNCTION)
#define IS_CLOSURE(value)       Object::isObjType(value, OBJ_CLOSURE)
#define IS_NATIVE(value)        Object::isObjType(value, OBJ_NATIVE)

/**
 * @enum ObjType
 * @brief Enumeration of the possible types of objects in Lax.
 */
enum ObjType {
    OBJ_STRING,
    OBJ_UPVALUE,
    OBJ_FUNCTION,
    OBJ_CLOSURE,
    OBJ_NATIVE
};

/**
 * @class Object
 * @brief Base class for all objects in Lax.
 *
 * All objects in Lax inherit from this class. It is used to store the type of
 * the object.
 *
 * @see ObjType
 */
class Object {
public:
    /**
     * @brief Class constructor.
     * @param type The type of the object.
     */
    explicit Object(ObjType type);

    /**
     * @brief Class destructor.
     *
     * This destructor is pure virtual, which means that this class cannot be
     * instantiated.
     */
    virtual ~Object() = 0;

    /**
     * @brief Returns the type of the object.
     * @return The object type.
     */
    ObjType getType();

    /**
     * @brief Returns a string representation of the object.
     * @return The string representation of the object.
     */
    virtual std::string toString();

    /**
     * @brief Checks if a value is of a given type.
     *
     * This function is implemented as a static function, so that it can be used
     * without instantiating an object.
     *
     * @param value The value to check.
     * @param type The expected type.
     * @return `true` if the value matches the type, `false` otherwise.
     */
    static inline bool isObjType(Value value, ObjType type) {
        return IS_OBJ(value) && OBJ_TYPE(value) == type;
    }

protected:
    ObjType m_type;
};

#endif // LAX_OBJECT_H

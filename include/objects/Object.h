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

/// Enumeration of the types of objects.
enum ObjType {
    OBJ_STRING,
    OBJ_UPVALUE,
    OBJ_FUNCTION,
    OBJ_CLOSURE,
    OBJ_NATIVE
};

/**
 * Represent an object in Lax as in the OOP paradigm.
 */
class Object {
public:
    /// Class constructor.
    explicit Object(ObjType type);

    /// Class destructor.
    virtual ~Object() = 0;

    /**
     * Return the type of the object.
     *
     * @return the object type.
     */
    ObjType getType();

    /**
     * Return a string representation of the object.
     *
     * @return the string representation.
     */
    virtual std::string toString();

    /**
     * Check if a value is of a specific object type.
     *
     * @param value the value to check.
     * @param type the expected type.
     * @return true if the value match the type.
     */
    static inline bool isObjType(Value value, ObjType type) {
        return IS_OBJ(value) && OBJ_TYPE(value) == type;
    }

protected:
    ObjType m_type;
};

#endif // LAX_OBJECT_H

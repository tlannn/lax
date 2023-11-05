#ifndef LAX_OBJECTTYPE_H
#define LAX_OBJECTTYPE_H

#include "LaxType.h"

/**
 * @class ObjectType
 * @brief Class representing the type of an object.
 *
 * This class is used to represent the type of an object in Lax. It is used to
 * distinguish objects from other types of values, and to perform type checking.
 *
 * An object type is defined by the type of data it contains.
 */
struct ObjectType : public LaxType {
public:
    /**
     * @brief Class constructor.
     */
    ObjectType();

    /**
     * @copydoc LaxType::toString()
     */
    std::string toString() const override;
};

#endif // LAX_OBJECTTYPE_H

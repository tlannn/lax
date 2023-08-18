#ifndef LAX_OBJECTTYPE_H
#define LAX_OBJECTTYPE_H

#include "LaxType.h"

struct ObjectType : public LaxType {
public:
    //Object::ObjType type;

    ObjectType();

    std::string toString() const override;
};

#endif // LAX_OBJECTTYPE_H

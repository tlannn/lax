#include "objects/Object.h"

Object::Object(ObjType type) :
    m_type(type) {}

Object::~Object() = default;

ObjType Object::getType() {
    return m_type;
}

std::string Object::toString() {
    return "<obj>";
}

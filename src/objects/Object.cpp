#include "objects/Object.h"

/// Class constructor.
Object::Object(ObjType type) :
    m_type(type) {}

/// Class destructor.
Object::~Object() = default;

/// Return the type of the object.
ObjType Object::getType() {
    return m_type;
}

/// Return a string representation of the object.
std::string Object::toString() {
    return "<obj>";
}

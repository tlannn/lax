#include "values/LaxType.h"
#include "values/FunctionType.h"
#include "values/ObjectType.h"
#include "values/PrimitiveType.h"

LaxType::LaxType(Kind kind) : m_kind(kind) {}

bool LaxType::isPrimitive(const LaxType &type) {
    return type.m_kind == PRIMITIVE;
}

bool LaxType::isFunction(const LaxType &type) {
    return type.m_kind == FUNCTION;
}

bool LaxType::isObject(const LaxType &type) {
    return type.m_kind == OBJECT;
}

PrimitiveType& LaxType::asPrimitive(LaxType &type) {
    return static_cast<PrimitiveType&>(type);
}

FunctionType& LaxType::asFunction(LaxType &type) {
    return static_cast<FunctionType&>(type);
}

ObjectType& LaxType::asObject(LaxType &type) {
    return static_cast<ObjectType&>(type);
}

const LaxType::Kind& LaxType::getKind() const {
    return m_kind;
}

bool operator==(const LaxType &t1, const LaxType &t2) {
    return typeid(t1) == typeid(t2) && t1.equals(t2);
}

bool operator!=(const LaxType &t1, const LaxType &t2) {
    return !(t1 == t2);
}

bool LaxType::equals(const LaxType &type) const {
    return m_kind == type.m_kind;
}

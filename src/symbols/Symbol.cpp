#include "symbols/Symbol.h"

Symbol::Symbol(ObjString* name, LaxType* type) :
    m_name(name),
    m_type(type) {}

ObjString* Symbol::getName() {
    return m_name;
}

LaxType* Symbol::getType() {
    return m_type;
}

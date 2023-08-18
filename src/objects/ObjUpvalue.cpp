#include "objects/ObjUpvalue.h"

ObjUpvalue::ObjUpvalue(Value* slot) : Object(ObjType::OBJ_UPVALUE),
    m_location(slot),
    m_closed(Value::null()),
    m_next(nullptr) {}

Value* ObjUpvalue::getLocation() const {
    return m_location;
}

ObjUpvalue* ObjUpvalue::getNext() const {
    return m_next;
}

void ObjUpvalue::setNext(ObjUpvalue* nextUpvalue) {
    m_next = nextUpvalue;
}

void ObjUpvalue::setClosed(Value value) {
    m_closed = value;
    m_location = &m_closed;
}

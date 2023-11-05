#include "objects/ObjClosure.h"
#include "objects/ObjFunction.h"

ObjClosure::ObjClosure(ObjFunction* function) : Object(ObjType::OBJ_CLOSURE),
    m_function(function),
    m_upvalueCount(function->getUpvalueCount())
{
    m_upvalues = new ObjUpvalue* [m_upvalueCount];

    // Initialize for garbage collector
    for (int i = 0; i < m_upvalueCount; ++i)
        m_upvalues[i] = nullptr;
}

ObjFunction* ObjClosure::getFunction() {
    return m_function;
}

ObjUpvalue** ObjClosure::getUpvalues() const {
    return m_upvalues;
}

int ObjClosure::getUpvalueCount() const {
    return m_upvalueCount;
}

std::string ObjClosure::toString() {
    return m_function->toString();
}

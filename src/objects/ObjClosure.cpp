#include "objects/ObjClosure.h"
#include "objects/ObjFunction.h"

/// Class constructor.
ObjClosure::ObjClosure(ObjFunction* function) : Object(ObjType::OBJ_CLOSURE),
    m_function(function),
    m_upvalueCount(function->getUpvalueCount())
{
    m_upvalues = new ObjUpvalue* [m_upvalueCount];

    // Initialize for garbage collector
    for (int i = 0; i < m_upvalueCount; ++i)
        m_upvalues[i] = nullptr;
}

/// Getter for the function referenced.
ObjFunction* ObjClosure::getFunction() {
    return m_function;
}

/// Getter for the upvalues captured by the closure.
ObjUpvalue** ObjClosure::getUpvalues() const {
    return m_upvalues;
}

/// Return the number of upvalues captured by the closure.
int ObjClosure::getUpvalueCount() const {
    return m_upvalueCount;
}

/// Return a string representation of the closure.
std::string ObjClosure::toString() {
    return m_function->toString();
}

#include "objects/ObjFunction.h"
#include "objects/ObjString.h"

/// Class constructor.
ObjFunction::ObjFunction(ObjString* name, int arity) :
    Object(ObjType::OBJ_FUNCTION),
    m_name(name),
    m_arity(arity),
    m_upvalueCount(0) {}

/// Getter for the number of parameters of the function.
int ObjFunction::arity() const {
    return m_arity;
}

/// Increment the number of upvalues used in the function.
void ObjFunction::incrementUpvalueCount() {
    m_upvalueCount++;
}

/// Return the number of upvalues used in the function.
int ObjFunction::getUpvalueCount() const {
    return m_upvalueCount;
}

/// Return a pointer to the chunk of bytecode that depicts the function.
Chunk* ObjFunction::getChunk() {
    return &m_chunk;
}

/// Return a string representation of the function.
std::string ObjFunction::toString() {
    return m_name ? "<fn " + m_name->toString() + ">" : "<script>";
}

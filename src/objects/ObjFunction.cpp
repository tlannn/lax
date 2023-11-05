#include "objects/ObjFunction.h"
#include "objects/ObjString.h"

ObjFunction::ObjFunction(ObjString* name, int arity) :
    Object(ObjType::OBJ_FUNCTION),
    m_name(name),
    m_arity(arity),
    m_upvalueCount(0) {}

int ObjFunction::arity() const {
    return m_arity;
}

void ObjFunction::incrementUpvalueCount() {
    m_upvalueCount++;
}

int ObjFunction::getUpvalueCount() const {
    return m_upvalueCount;
}

Chunk* ObjFunction::getChunk() {
    return &m_chunk;
}

std::string ObjFunction::toString() {
    return m_name ? "<fn " + m_name->toString() + ">" : "<script>";
}

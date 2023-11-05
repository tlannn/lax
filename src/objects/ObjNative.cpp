#include "objects/ObjNative.h"

ObjNative::ObjNative(NativeFn function) : Object(ObjType::OBJ_NATIVE),
    m_function(function) {}

NativeFn ObjNative::getFunction() {
    return m_function;
}

std::string ObjNative::toString() {
    return "<native fn>";
}

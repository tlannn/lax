#include "objects/ObjString.h"
#include "common/StringTable.h"

/// Class constructor.
ObjString::ObjString(std::string chars) : Object(ObjType::OBJ_STRING),
    m_length(static_cast<int>(chars.size())),
    m_chars(std::move(chars)),
    m_hash(hashString(m_chars, m_length)) {}

/// Create a string in the heap memory and add intern it in the string pool.
ObjString* ObjString::allocateString(const std::string& string) {
    auto* stringObject = new ObjString(string);
    auto stringPtr = std::unique_ptr<ObjString>(stringObject);

    StringTable::instance()->insert(std::move(stringPtr));

    return stringObject;
}

/// Copy a string object from the string pool.
///
/// If the string is not already interned in the string pool, then a new
/// string object is created in the heap memory.
ObjString* ObjString::copyString(const std::string& string) {
    int stringSize = static_cast<int>(string.size());
    uint32_t stringHash = ObjString::hashString(string, stringSize);

    ObjString* stringObject = StringTable::instance()->get(string, stringSize, stringHash);

    if (stringObject) return stringObject;

    return allocateString(string);
}

/// Hash a string using the FNV-1a algorithm.
uint32_t ObjString::hashString(const std::string& string, int length) {
    uint32_t hash = 2166136261u;
    for (int i = 0; i < length; i++) {
        hash ^= (uint8_t)string[i];
        hash *= 16777619;
    }
    return hash;
}

/// Getter for the length of the string.
int ObjString::getLength() const {
    return m_length;
}

/// Getter for the hash of the string.
uint32_t ObjString::getHash() const {
    return m_hash;
}

/// Return the object as a C string.
const char* ObjString::getChars() {
    return m_chars.c_str();
}

/// Return the object as a C++ string.
std::string ObjString::toString() {
    return m_chars;
}

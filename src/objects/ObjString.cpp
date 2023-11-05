#include "objects/ObjString.h"
#include "common/StringTable.h"

ObjString::ObjString(std::string chars) : Object(ObjType::OBJ_STRING),
    m_length(static_cast<int>(chars.size())),
    m_chars(std::move(chars)),
    m_hash(hashString(m_chars, m_length)) {}

ObjString* ObjString::allocateString(const std::string& string) {
    auto* stringObject = new ObjString(string);
    auto stringPtr = std::unique_ptr<ObjString>(stringObject);

    StringTable::instance()->insert(std::move(stringPtr));

    return stringObject;
}

ObjString* ObjString::copyString(const std::string& string) {
    int stringSize = static_cast<int>(string.size());
    uint32_t stringHash = ObjString::hashString(string, stringSize);

    ObjString* stringObject = StringTable::instance()->get(string, stringSize, stringHash);

    if (stringObject) return stringObject;

    return allocateString(string);
}

uint32_t ObjString::hashString(const std::string& string, int length) {
    uint32_t hash = 2166136261u;
    for (int i = 0; i < length; i++) {
        hash ^= (uint8_t)string[i];
        hash *= 16777619;
    }
    return hash;
}

int ObjString::getLength() const {
    return m_length;
}

uint32_t ObjString::getHash() const {
    return m_hash;
}

const char* ObjString::getChars() {
    return m_chars.c_str();
}

std::string ObjString::toString() {
    return m_chars;
}

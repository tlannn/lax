#include "common/StringTable.h"

StringTable::StringTable() :
    m_count(0),
    m_capacity(0),
    m_interned(nullptr) {}

StringTable::~StringTable() {
    delete[] m_interned;
}

std::shared_ptr<StringTable> StringTable::instance() {
    static std::shared_ptr<StringTable> instance{ new StringTable };
    return instance;
}

ObjString* StringTable::get(const std::string& chars, int length, uint32_t hash) {
    if (m_count == 0) return nullptr;

    auto& string = find(m_interned, m_capacity, chars,
        length, hash
    );

    if (string) return string.get();

    return nullptr;
}

bool StringTable::insert(std::unique_ptr<ObjString> key) {
    // Expand the table capacity if the table max load is reached
    if (m_count + 1 > m_capacity * TABLE_MAX_LOAD) {
        int capacity = GROW_CAPACITY(m_capacity);
        adjustCapacity(capacity);
    }

    // Find the entry corresponding to the key
    auto& entry = find(m_interned, m_capacity,
        key->getChars(), key->getLength(), key->getHash()
    );
    bool isNewKey = entry == nullptr;
    if (isNewKey) ++m_count;

    entry = std::move(key);
    return isNewKey;
}

bool StringTable::remove(ObjString* key) {
    if (m_count == 0) return false;

    // Find the entry
    auto& entry = find(m_interned, m_capacity,
        key->getChars(), key->getLength(), key->getHash()
    );
    if (entry == nullptr) return false;

    entry = nullptr;
    return true;
}

void StringTable::adjustCapacity(int capacity) {
    auto* entries = new std::unique_ptr<ObjString>[capacity];
    m_count = 0;

    // Create all new entries for strings
    for (int i = 0; i < m_capacity; ++i) {
        entries[i] = std::unique_ptr<ObjString>();
    }

    // Move previous strings in new entry set
    for (int i = 0; i < m_capacity; ++i) {
        auto& entry = m_interned[i];
        if (entry == nullptr) continue;

        auto& dest = find(entries, capacity,
            entry->getChars(), entry->getLength(), entry->getHash()
        );
        dest = std::move(entry);

        ++m_count;
    }

    delete[] m_interned;

    m_interned = entries;
    m_capacity = capacity;
}

std::unique_ptr<ObjString>& StringTable::find(std::unique_ptr<ObjString>* entries,
    int capacity, const std::string& chars, int length, uint32_t hash) {
    uint32_t index = hash % capacity;

    for (;;) {
        auto& entry = entries[index];
        if (entry == nullptr) return entry;

        bool isSameHash = entry->getHash() == hash;
        bool isSameLength = entry->getLength() == length;

        if (isSameHash && isSameLength &&
            memcmp(entry->getChars(), chars.c_str(), length) == 0) {
            return entry;
        }

        index = (index + 1) % capacity;
    }
}

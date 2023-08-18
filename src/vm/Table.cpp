#include "vm/Table.h"

/// Class constructor.
Table::Table() :
    m_count(0),
    m_capacity(0),
    m_entries(nullptr) {}

/// Class destructor.
Table::~Table() {
    delete[] m_entries;
}

/// Get a value stored in the table.
bool Table::get(ObjString* key, Value* value) {
    if (m_count == 0) return false;

    Entry* entry = find(m_entries, m_capacity, key);
    if (entry->key == nullptr) return false;

    *value = entry->value;
    return true;
}

/// Store a value in the table with the given key.
bool Table::set(ObjString* key, Value value) {
    // Expand the table capacity if the table max load is reached
    if (m_count + 1 > m_capacity * TABLE_MAX_LOAD) {
        int capacity = GROW_CAPACITY(m_capacity);
        adjustCapacity(capacity);
    }

    // Find the entry corresponding to the key
    Entry* entry = find(m_entries, m_capacity, key);
    bool isNewKey = entry->key == nullptr;

    // Increment the number of values stored only if no values was associated
    // to that key before
    if (isNewKey && IS_NULL(entry->value)) ++m_count;

    entry->key = key;
    entry->value = value;
    return isNewKey;
}

/// Remove from the table the value associated to the given key.
bool Table::remove(ObjString* key) {
    if (m_count == 0) return false;

    // Find the entry corresponding to the key
    Entry* entry = find(m_entries, m_capacity, key);
    if (entry->key == nullptr) return false;

    // Place a tombstone in the entry
    // This allows hash collisions to work even if the entry is now empty
    entry->key = nullptr;
    entry->value = Value::boolean(true);
    return true;
}

void Table::copyTable(Table* to) {
    for (int i = 0; i < m_capacity; ++i) {
        Entry* entry = &m_entries[i];

        if (entry->key != nullptr)
            to->set(entry->key, entry->value);
    }
}

ObjString* Table::findString(const std::string& chars, int length, uint32_t hash) {
    if (m_count == 0) return nullptr;

    uint32_t index = hash % m_capacity;

    for (;;) {
        Entry* entry = &m_entries[index];

        if (entry->key == nullptr && IS_NULL(entry->value)) return nullptr;

        else if (entry->key->getLength() == length &&
                 entry->key->getHash() == hash &&
                 memcmp(entry->key->getChars(), chars.c_str(), length) == 0)
        {
            return entry->key;
        }

        index = (index + 1) % m_capacity;
    }
}

/// Resize the table to accept a new amount of entries.
void Table::adjustCapacity(int capacity) {
    auto* entries = new Entry[capacity];

    // Initialize all new entries
    for (int i = 0; i < capacity; ++i) {
        entries[i].key = nullptr;
        entries[i].value = Value::null();
    }

    m_count = 0;

    // Copy all entries previously stored
    for (int i = 0; i < m_capacity; ++i) {
        Entry* entry = &m_entries[i];
        if (entry->key == nullptr) continue;

        // Each values get rehashed since the table size is not the same
        Entry* dest = find(entries, capacity, entry->key);
        dest->key = entry->key;
        dest->value = entry->value;
        ++m_count;
    }

    // Free memory reserved by previous entries
    delete[] m_entries;

    m_entries = entries;
    m_capacity = capacity;
}

/// Find the entry corresponding to a key in an array of entries.
Table::Entry* Table::find(Entry* entries, int capacity, ObjString* key) {
    uint32_t index = key->getHash() % capacity;
    Entry* tombstone = nullptr;

    // Loop is safe since hash table is never full due to max load
    for (;;) {
        Entry* entry = &entries[index];

        if (entry->key == nullptr) {
            // Entry is empty
            if (IS_NULL(entry->value))
                return tombstone != nullptr ? tombstone : entry;

            // Tombstone found
            else if (tombstone == nullptr) tombstone = entry;
        }

        // Key found
        else if (entry->key == key) return entry;

        // Since the table uses open hashing, hash collisions are resolved via
        // linear probing
        index = (index + 1) % capacity;
    }
}

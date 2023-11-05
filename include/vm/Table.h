#ifndef LAX_TABLE_H
#define LAX_TABLE_H

#include <cstring>

#include "common/Memory.h"
#include "objects/ObjString.h"
#include "values/Value.h"

#define TABLE_MAX_LOAD 0.75

/**
 * @class Table
 * @brief A hash table to store Lax values.
 *
 * The table is implemented as a closed hash table. The array of key-value pairs
 * is allocated on the heap, and the array is resized when the load primary
 * exceeds the maximum load primary.
 *
 * Keys are represented as Lax string objects. Key collisions are resolved using
 * open addressing. The next slot is computed via linear probing.
 *
 * The hash function used is defined in the ObjString class.
 */
class Table {
public:
    /**
     * @brief Class constructor.
     *
     * Initializes the table with a null array of entries.
     */
    Table();

    /**
     * @brief Class destructor.
     *
     * Frees the memory allocated for the table.
     */
    ~Table();

    /**
     * @brief Retrieves the value associated to a key in the table.
     * @param key The key associated with the value.
     * @param value The value object where the value copy must be stored.
     * @return `true` if the key exists, `false` otherwise.
     */
    bool get(ObjString* key, Value* value);

    /**
     * @brief Stores a value in the table.
     * @param key The key associated with the value.
     * @param value The value to store.
     * @return `true` if no value was already associated to the key, `false`
     * otherwise.
     */
    bool set(ObjString* key, Value value);

    /**
     * @brief Removes a value from the table.
     * @param key The key associated with the value.
     * @return `true` if a value has effectively been removed, `false` otherwise.
     */
    bool remove(ObjString* key);

    /**
     * @brief Copies the content of a table into another.
     * @param to The table to copy into.
     */
    void copyTable(Table* to);

    /**
     * @brief Searches for a string in the table.
     * @param chars The string to look up.
     * @param length The length of the string.
     * @param hash The hash of the string.
     * @return The string object if it exists, or nullptr otherwise.
     */
    ObjString* findString(const std::string& chars, int length, uint32_t hash);

private:
    /**
     * @struct Entry
     * @brief A key-value pair stored in the table.
     *
     * The key is a Lax string object, and the value is a Lax value object.
     */
    typedef struct Entry {
        ObjString* key = nullptr;
        Value value = Value::null();
    } Entry;

    /**
     * @brief Adjusts the capacity of the table.
     *
     * This function is called when the load primary of the table exceeds the
     * maximum load primary.
     *
     * @param capacity The new capacity of the table.
     */
    void adjustCapacity(int capacity);

    /**
     * @brief Finds an entry in an array of entries.
     *
     * This function uses linear probing to find the entry corresponding to the
     * given key.
     *
     * @param entries The array of entries to look up.
     * @param capacity The capacity of the array.
     * @param key The key to look up.
     * @return The entry corresponding to the key.
     */
    static Entry* find(Entry* entries, int capacity, ObjString* key);

    int m_count;
    int m_capacity;
    Entry* m_entries;
};

#endif //LAX_TABLE_H

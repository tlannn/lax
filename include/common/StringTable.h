#ifndef LAX_STRINGTABLE_H
#define LAX_STRINGTABLE_H

#include <cstring>
#include <memory>

#include "objects/ObjString.h"

#define TABLE_MAX_LOAD 0.75

/**
 * @class StringTable
 * @brief A table of string objects.
 *
 * This class implements a table of string objects. It is used to store all the
 * string objects created during the execution of the program. This allows to
 * avoid creating multiple string objects for the same string.
 *
 * The table is implemented as a hash table, where the hash of a string is used
 * to find the entry associated to the string. The table is dynamically resized
 * when the load primary exceeds a certain threshold.
 *
 * @note This class is implemented as a singleton.
 *
 * @see ObjString
 */
class StringTable {
public:
    /**
     * @brief Class destructor.
     *
     * Frees the memory allocated for the table.
     */
    ~StringTable();

    /// Remove the copy constructor.
    StringTable(const StringTable&) = delete;

    /// Remove the assignment operator.
    StringTable& operator=(const StringTable&) = delete;

    /**
     * @brief Returns the singleton instance of the string table.
     * @return The singleton instance of the string table.
     */
    static std::shared_ptr<StringTable> instance();

    /**
     * @brief Retrieves a string object stored in the table.
     * @param chars The string to lookup.
     * @param length The length of the string.
     * @param hash The hash of the string.
     * @return The string object associated to the string, or nullptr if no
     * string object is associated to the string.
     */
    ObjString* get(const std::string& chars, int length, uint32_t hash);

    /**
     * @brief Stores a string object in the table.
     *
     * The string object is stored in the table, but not copied ; the ownership
     * of the string object is transferred to the table.
     *
     * If the table is full, it is resized.
     *
     * If the string is already in the table, then the string object overwrites
     * the existing one.
     *
     * @param key The string object to store.
     * @return `true` if the string was not already stored in the table.
     */
    bool insert(std::unique_ptr<ObjString> key);

    /**
     * @brief Removes a string object from the table.
     *
     * The string object is removed from the table, but not freed from the heap
     * memory.
     *
     * @param key The string object to remove.
     * @return `true` if the string was effectively in the table and has been
     * removed.
     */
    bool remove(ObjString* key);

private:
    /**
     * @brief Class constructor.
     *
     * The constructor initializes the table with a default capacity.
     */
    StringTable();

    /**
     * @brief Resizes the table to accept a new amount of entries.
     * @param capacity The new capacity of the table.
     */
    void adjustCapacity(int capacity);

    /**
     * @brief Finds the entry associated to a string in the table.
     * @param entries The array of strings to look up.
     * @param capacity The capacity of the array.
     * @param chars The string to search.
     * @param length The length of the string.
     * @param hash The hash of the string.
     * @return The entry associated to the string, or nullptr if no entry is
     * associated to the string.
     */
    static std::unique_ptr<ObjString>& find(std::unique_ptr<ObjString>* entries,
        int capacity, const std::string& chars, int length, uint32_t hash);

    int m_count;
    int m_capacity;
    std::unique_ptr<ObjString>* m_interned;
};

#endif //LAX_STRINGTABLE_H

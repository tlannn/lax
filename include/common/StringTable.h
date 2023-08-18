#ifndef LAX_STRINGTABLE_H
#define LAX_STRINGTABLE_H

#include <cstring>
#include <memory>

#include "objects/ObjString.h"

#define TABLE_MAX_LOAD 0.75

class StringTable {
public:
    /// Class destructor.
    ~StringTable();

    /// Copy constructor.
    StringTable(const StringTable&) = delete;

    /// Remove the assignment operator.
    StringTable& operator=(const StringTable&) = delete;

    /**
     * Return a singleton of the class.
     * @return the singleton class instance.
     */
    static std::shared_ptr<StringTable> instance();

    /**
     * Get a string object stored in the table.
     *
     * @param chars the string to lookup.
     * @param length the length of the string.
     * @param hash the hash of the string.
     * @return a pointer to the string object, or nullptr if the string isn't
     * in the table.
     */
    ObjString* get(const std::string& chars, int length, uint32_t hash);

    /**
     * Store a string object in the table.
     *
     * @param key the string object to store.
     * @return true if the string was not already stored in the table.
     */
    bool insert(std::unique_ptr<ObjString> key);

    /**
     * Remove a string object from the table.
     *
     * @param key the string object to remove.
     * @return true if the string was effectively in the table and has been
     * removed.
     */
    bool remove(ObjString* key);

private:
    /// Class constructor.
    StringTable();

    /**
     * Resize the table to accept a new amount of entries.
     *
     * @param capacity the new capacity of the table.
     */
    void adjustCapacity(int capacity);

    /**
     * Find the entry associated to a string in an array of string objects.
     *
     * @param entries the array of strings to look up.
     * @param capacity the capacity of the array.
     * @param chars the string to search.
     * @param length the length of the string.
     * @param hash the hash of the string.
     * @return a reference to the entry associated to the string.
     */
    static std::unique_ptr<ObjString>& find(std::unique_ptr<ObjString>* entries,
        int capacity, const std::string& chars, int length, uint32_t hash);

    int m_count;
    int m_capacity;
    std::unique_ptr<ObjString>* m_interned;
};

#endif //LAX_STRINGTABLE_H

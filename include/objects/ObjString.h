#ifndef LAX_OBJSTRING_H
#define LAX_OBJSTRING_H

#include <string>
#include <unordered_set>

#include "objects/Object.h"

/**
 * String object in Lax.
 *
 * A string is a sequence of characters. Strings are a primitive type of Lax.
 * But since they may vary in length (i.e. memory size), they cannot be
 * implemented like an integer or a boolean. Thus, they are constructed as an
 * object.
 *
 * String interning is performed for each string created. That means that a
 * string pool stores every string objects. As a consequence, instead of
 * manipulating a string object directly, it can only be manipulated via a
 * pointer to it.
 */
class ObjString : public Object {
public:
    /// Class destructor.
    ~ObjString() override = default;

    /**
     * Copy a string object from the string pool.
     *
     * If the string is not already interned in the string pool, then a new
     * string object is created in the heap memory.
     *
     * @param string the string to copy from the string pool.
     * @return a pointer to the heap-allocated string object.
     */
    static ObjString* copyString(const std::string& string);

    /**
     * Hash a string using the FNV-1a algorithm.
     *
     * @param string the string to hash.
     * @param length the length of the string.
     * @return the hash of the string.
     */
    static uint32_t hashString(const std::string& string, int length);

    /**
     * Getter for the length of the string.
     *
     * @return the number of characters in the string.
     */
    int getLength() const;

    /**
     * Getter for the hash of the string.
     *
     * @return the hash of the string.
     */
    uint32_t getHash() const;

    /**
     * Return the object as a C string.
     *
     * @return the C string.
     */
    const char* getChars();

    /**
     * Return the object as a C++ string.
     *
     * @return the C++ string.
     */
    std::string toString() override;

private:
    /**
     * Class constructor.
     *
     * @param chars the characters of the string.
     */
    explicit ObjString(std::string chars);

    /**
     * Create a string in the heap memory and add intern it in the string pool.
     *
     * @param string the string to create and intern.
     * @return a pointer to the heap-allocated string object.
     */
    static ObjString* allocateString(const std::string& string);

    int m_length;
    std::string m_chars;
    uint32_t m_hash;
};

#define AS_STRING(value)        ((dynamic_cast<ObjString*>(AS_OBJ(value))))

#endif // LAX_OBJSTRING_H

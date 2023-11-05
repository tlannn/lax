#ifndef LAX_OBJSTRING_H
#define LAX_OBJSTRING_H

#include <string>
#include <unordered_set>

#include "objects/Object.h"

/**
 * @class ObjString
 * @brief String object in Lax.
 *
 * A string is a sequence of characters. Strings are a primitive type of Lax.
 * But since they may vary in length (i.e. memory size), they cannot be
 * implemented like an integer or a boolean. Thus, they are constructed as an
 * object.
 *
 * Strings are immutable. That means that once a string is created, it cannot be
 * modified. If a string is modified, then a new string is created.
 *
 * Strings are interned in a string pool. That means that if two strings are
 * equal, then they are the same object. This is useful for string comparison.
 *
 * The hash of a string is computed using the FNV-1a algorithm. This hash is
 * used to speed up string comparison.
 *
 * String interning is performed for each string created. That means that a
 * string pool stores every string objects. As a consequence, instead of
 * manipulating a string object directly, it can only be manipulated via a
 * pointer to it.
 */
class ObjString : public Object {
public:
    /**
     * @brief Class destructor.
     *
     * This destructor is used to deallocate any resources held by the ObjString
     * object.
     *
     * @note This destructor is explicitly set to use the default implementation
     *       provided by the compiler. It means that the compiler-generated
     *       destructor will be used.
     */
    ~ObjString() override = default;

    /**
     * @brief Retrieves a string object from the string pool.
     *
     * If the string is not already interned in the string pool, then a new
     * string object is created in the heap memory.
     *
     * @param string The string to copy from the string pool.
     * @return A pointer to the heap-allocated string object.
     */
    static ObjString* copyString(const std::string& string);

    /**
     * @brief Hashes a string using the FNV-1a algorithm.
     * @param string The string to hash.
     * @param length The length of the string.
     * @return The hash of the string.
     */
    static uint32_t hashString(const std::string& string, int length);

    /**
     * @brief Returns the length of the string.
     * @return The number of characters in the string.
     */
    int getLength() const;

    /**
     * @brief Returns the hash of the string.
     * @return The hash of the string.
     */
    uint32_t getHash() const;

    /**
     * @brief Returns the string object as a C string.
     *
     * This function is used to retrieve the string as a C string. This is
     * useful for printing the string, for example.
     *
     * @note The returned C string is a handle to internal memory. Thus, it is
     *       unsafe to modify it. That is why the returned C string is constant,
     *       to make it read-only.
     *
     * @return The C string.
     */
    const char* getChars();

    /**
     * @brief Returns the string object as a C++ string.
     *
     * This function is used to retrieve the string as a C++ string. This is
     * useful for printing the string, for example.
     *
     * @note The returned C++ string is a copy of the string. Thus, it is safe
     *       to modify it.
     *
     * @return The C++ string.
     */
    std::string toString() override;

private:
    /**
     * @brief Class constructor.
     *
     * This constructor is used to create a string object from a sequence of
     * characters.
     *
     * @param chars The characters of the string.
     */
    explicit ObjString(std::string chars);

    /**
     * @brief Allocates a string object in the heap memory.
     *
     * This function is private because strings are interned in the string pool.
     * Thus, the only way to create a string object is to use the copyString
     * function.
     *
     * @param string The string to create and intern.
     * @return A pointer to the heap-allocated string object.
     *
     * @see copyString
     */
    static ObjString* allocateString(const std::string& string);

    int m_length;
    std::string m_chars;
    uint32_t m_hash;
};

#define AS_STRING(value)        ((dynamic_cast<ObjString*>(AS_OBJ(value))))

#endif // LAX_OBJSTRING_H

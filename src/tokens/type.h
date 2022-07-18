#ifndef LAX_TYPE_H
#define LAX_TYPE_H

#include "token.h"
#include "tokentype.h"

/**
 * Type lookup table constants
 */
#define _int 0
#define _bool 1
#define _undef 2

/// Lookup tables for resulting types in arithmetic and logical operations
extern int addOpLookup[2][2];
extern int subOpLookup[2][2];
extern int mulOpLookup[2][2];
extern int divOpLookup[2][2];
extern int logicOpLookup[2][2];
extern int relOpLookup[2][2];

/// Lax primitive types
typedef bool lBool;
typedef int lInt;

/**
 *
 */
class Type : public Token {
public:
	static Type NONE; // Not a valid type
    static Type INT; // Basic type 'int' for integers
    static Type BOOL; // Basic type 'bool' for booleans
    static Type STRING; // Basic type 'bool' for booleans

	/**
	 * Return the type from a token representing a type keyword
	 * @param tok the token representing a type
	 * @return the type associated
	 */
	static Type* getType(Token *tok);

    /**
     * Getter for the type size
     *
     * @return the size in bytes of the type
     */
    int getSize() const;

	/**
	 * Determine the wider type in a binary operation
	 *
	 * @param t1 the first type to compare
	 * @param op the operator of the operation
	 * @param t2 the second type to compare
	 * @return the wider type
	 */
	static Type max(const Type &t1, const Token &op, const Type &t2);

	/**
	 * Check if the given type is a numeric
	 *
	 * @param t the type to check
	 * @return true if the type is a numeric
	 */
	static bool numeric(const Type &t);

    /**
     * Overload the equality operator to compare two types
     *
     * @param t1 the first type to compare
     * @param t2 the second type to compare
     * @return true if the two types are equal
     */
    friend bool operator== (const Type &t1, const Type &t2);

    /**
     * Overload the not equal operator to compare two types
     *
     * @param t1 the first type to compare
     * @param t2 the second type to compare
     * @return true if the two types are not equal
     */
    friend bool operator!= (const Type &t1, const Type &t2);

protected:
    int _size;

    /**
     * Class constructor
     *
     * @param word the word representing the type
     * @param type the type of the token
     * @param size the size in bytes for the type
     */
    Type(const std::string &word, TokenType type, int size);

	/**
	 * Convert a type to a integer value
	 *
	 * @param type the type to convert
	 * @return the integer value of the type
	 */
	static int typeToInt(const Type &type);

	/**
	 * Convert a type integer value to a type
	 *
	 * @param type the integer value to convert
	 * @return the type represented by the integer value
	 */
	static Type intToType(int i);
};

#endif // LAX_TYPE_H

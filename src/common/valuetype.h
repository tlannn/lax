#ifndef LAX_VALUETYPE_H
#define LAX_VALUETYPE_H

#include "tokens/token.h"
#include "tokens/tokentype.h"

/**
 * Handler class for Lax types
 *
 * Allow the use of Lax types as object in the C++ code.
 */
class ValueType {
public:
	/**
	 * Enumeration of the primitive types in Lax
	 */
	enum Type: char {
		VAL_NULL,
		VAL_BOOL,
		VAL_INT,
		VAL_OBJ
	};

	/**
	 * Class constructor
	 * @param type the type of a value
	 */
	ValueType(ValueType::Type type);

	/**
	 * Check whether a type is numeric or not
	 * @param t the type to check
	 * @return true if the type is numeric
	 */
	static bool isNumeric(const ValueType::Type &t);

	/**
	 * Determine the wider type in a binary operation
	 * @param t1 the first type to compare
	 * @param op the operator
	 * @param t2 the second type to compare
	 * @return the wider type
	 */
	static ValueType::Type max(const ValueType::Type &t1, const Token &op, const ValueType::Type &t2);

	/**
	 * Return the type corresponding to a type keyword
	 * @param tok the token representing the type keyword
	 * @return the corresponding type
	 */
	static ValueType::Type getType(Token *tok);

	/**
	 * Return a string representation of a type
	 * @param t the type
	 * @return the string representation
	 */
	static std::string toString(const ValueType &t);

	/**
	 * Allow the use the type in a switch statement
	 */
	operator Type() const;

	/**
	 * Disable the use of the type in a condition
	 */
	explicit operator bool() const = delete;

	/**
	 * Overload the behavior of the assign operator when the assigned value is
	 * a type object
	 * @param t the type
	 * @return the corresponding type object
	 */
	ValueType& operator=(const ValueType &t);

	/**
	 * Overload the behavior of the assign operator when the assigned value is
	 * an enumeration type value
	 * @param t the type
	 * @return the corresponding type object
	 */
	ValueType& operator=(const ValueType::Type &t);

	/**
	 * Overload the behavior of the equality operator
	 * @param t1 the type object
	 * @param t2 the type enumeration value
	 * @return true if the two types are considered equal
	 */
	friend bool operator==(ValueType t1, ValueType::Type t2);

	/**
	 * Overload the behavior of the non-equality operator
	 * @param t1 the type object
	 * @param t2 the type enumeration value
	 * @return true if the two types are considered non-equal
	 */
	friend bool operator!=(ValueType t1, ValueType::Type t2);

private:
	Type _type;

	/// Lookup tables for resulting types in arithmetic and logical operations
	static ValueType::Type addOpLookup[3][3];
	static ValueType::Type subOpLookup[3][3];
	static ValueType::Type mulOpLookup[3][3];
	static ValueType::Type divOpLookup[3][3];
	static ValueType::Type logicOpLookup[3][3];
	static ValueType::Type relOpLookup[3][3];
};

#endif // LAX_VALUETYPE_H

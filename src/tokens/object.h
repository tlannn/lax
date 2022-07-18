#ifndef LAX_OBJECT_H
#define LAX_OBJECT_H

#include <string>

#include "type.h"

/**
 * Represent an object as in the OOP paradigm
 */
class Object {
public:
	static Object null;

	/**
	 * Default class constructor
	 */
	Object();

	/**
	 * Class constructor
	 * @param i the integer to turn to an object
	 */
	explicit Object(int i);

	/**
	 * Class constructor
	 * @param b the boolean to turn to an object
	 */
	explicit Object(bool b);

	/**
	 * Class constructor
	 * @param s the string to turn to an object
	 */
	explicit Object(std::string s);

	/**
	 * Return for the integer representation of the object
	 * @return the integer value
	 */
	int toInt() const;

	/**
	 * Return for the boolean representation of the object
	 * @return the boolean value
	 */
	bool toBool() const;

	/**
	 * Return for the string representation of the object
	 * @return the string value
	 */
	std::string toString() const;

private:
	/**
	 * Represent a primitive value of the language
	 */
	union Value {
		lBool b;
		lInt i;
	};

	Type _type; // The type of the object
	Value _value; // The primitive value of the object
	std::string _stringValue; // The string value of the object
};

#endif // LAX_OBJECT_H

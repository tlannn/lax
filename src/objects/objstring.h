#ifndef LAX_OBJSTRING_H
#define LAX_OBJSTRING_H

#include "object.h"

/**
 * String object in Lax
 *
 * A string is a sequence of characters. Strings are a primitive type of Lax.
 * But since they may vary in length (i.e. memory size), they cannot be
 * implemented like an integer or a boolean. Thus, they are constructed as an
 * object.
 */
class ObjString : public Object {
public:
	/**
	 * Class constructor
	 */
	ObjString();

	/**
	 * Class constructor
	 * @param chars the characters of the string
	 */
	explicit ObjString(std::string chars);

	/**
	 * Class destructor
	 */
	~ObjString() override = default;

	/**
	 * Getter for the length of the string
	 * @return the number of characters in the string
	 */
	int getLength();

	/**
	 * Return the string
	 * @return the string
	 */
	std::string toString() override;

private:
	int _length;
	std::string _chars;
};

#define AS_STRING(value)		((dynamic_cast<String*>(AS_OBJ(value))))
#define AS_CPPSTRING(value)		(AS_OBJ(value)->toString())

#endif // LAX_OBJSTRING_H

#ifndef LAX_VARIABLE_H
#define LAX_VARIABLE_H

#include <memory>

#include "common/valuetype.h"
#include "tokens/token.h"

/**
 * Represent a variable
 */
class Variable {
public:
	/**
	 * Class constructor
	 * @param varName the name of the variable
	 * @param type the type of the variable
	 */
	Variable(std::unique_ptr<Token> varName, ValueType type);

	/**
	 * Getter for the variable name
	 * @return the variable name
	 */
	Token* getVarName() const;

	/**
	 * Getter for the variable type
	 * @return the variable type
	 */
	ValueType getType() const;

private:
	std::unique_ptr<Token> _name;
	ValueType _type;
};

#endif // LAX_VARIABLE_H

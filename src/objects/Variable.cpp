#include "objects/Variable.h"

/// Class constructor
Variable::Variable(std::unique_ptr<Token> varName, ValueType type) : _name(std::move(varName)), _type(type) {}

/// Getter for the variable name
Token* Variable::getVarName() const {
	return _name.get();
}

/// Getter for the variable type
ValueType Variable::getType() const {
	return _type;
}

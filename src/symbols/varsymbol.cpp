#include "varsymbol.h"

/// Class constructor
VarSymbol::VarSymbol(std::string name, ValueType &type) : Symbol(std::move(name), type) {}

/// Change the type of the variable
void VarSymbol::setType(ValueType type) {
	_type = type;
}

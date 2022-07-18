#include "varsymbol.h"

/// Class constructor
VarSymbol::VarSymbol(std::string &name, Type &type) : Symbol(name, type) {}

/// Change the type of the variable
void VarSymbol::setType(Type type) {
	_type = type;
}

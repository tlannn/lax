#include "funsymbol.h"

/// Class constructor
FunSymbol::FunSymbol(std::string name, std::vector<std::unique_ptr<VarSymbol>> args, ValueType returnType) :
					 Symbol(std::move(name), returnType), _args(std::move(args)) {}

/// Getter for the function arguments
const std::vector<std::unique_ptr<VarSymbol>>& FunSymbol::getArgs() {
	return _args;
}

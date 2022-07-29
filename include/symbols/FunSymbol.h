#ifndef LAX_FUNSYMBOL_H
#define LAX_FUNSYMBOL_H

#include <memory>
#include <string>
#include <vector>

#include "Symbol.h"
#include "VarSymbol.h"
#include "common/ValueType.h"

/**
 * Symbol representing a function
 */
class FunSymbol : public Symbol {
public:
	/**
	 * Class constructor
	 * @param name the function name
	 * @param args the arguments expected by the function
	 * @param _returnType the value type returned
	 */
	FunSymbol(std::string name, std::vector<std::unique_ptr<VarSymbol>> args, ValueType _returnType);

	/**
	 * Class destructor
	 */
	~FunSymbol() override = default;

	/**
	 * Getter for the function arguments
	 * @return the arguments expected
	 */
	const std::vector<std::unique_ptr<VarSymbol>>& getArgs();

private:
	std::vector<std::unique_ptr<VarSymbol>> _args;
};


#endif // LAX_FUNSYMBOL_H

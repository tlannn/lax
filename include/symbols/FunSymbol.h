#ifndef LAX_FUNSYMBOL_H
#define LAX_FUNSYMBOL_H

#define ARGS_TYPE std::vector<VarSymbol>

#include <memory>
#include <string>
#include <vector>

#include "Symbol.h"
#include "VarSymbol.h"

// Forward declarations
class LaxType;
class ObjString;

/**
 * Symbol representing a function
 */
class FunSymbol : public Symbol {
public:
	/**
	 * Class constructor
	 * @param name the function name
	 * @param args the arguments expected by the function
	 * @param returnType the value type returned
	 */
	FunSymbol(ObjString *name, ARGS_TYPE &args, LaxType *returnType);

	/**
	 * Getter for the function arguments
	 * @return the arguments expected
	 */
	const ARGS_TYPE& getArgs();

    Type getSymbolType() override;

private:
    ARGS_TYPE m_args;
};

#undef ARGS_TYPE

#endif // LAX_FUNSYMBOL_H

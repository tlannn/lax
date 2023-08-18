#ifndef LAX_BUILTINSYMBOL_H
#define LAX_BUILTINSYMBOL_H

#include <memory>
#include <string>
#include <vector>

#include "Symbol.h"
#include "VarSymbol.h"
#include "values/Value.h"

// Forward declarations
class LaxType;
class ObjString;

/**
 * Symbol representing a built-in type.
 */
class BuiltInSymbol : public Symbol {
public:
    /**
     * Class constructor
     * @param name the function name
     * @param args the arguments expected by the function
     * @param returnType the value type returned
     */
    BuiltInSymbol(ObjString* name, LaxType* type);

    Type getSymbolType() override;
};

#endif // LAX_BUILTINSYMBOL_H

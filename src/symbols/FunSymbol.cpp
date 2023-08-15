#include "symbols/FunSymbol.h"
#include "objects/ObjString.h"
#include "values/FunctionType.h"

/// Class constructor
FunSymbol::FunSymbol(
    ObjString *name,
    std::vector<VarSymbol> &args,
    LaxType *returnType
) : Symbol(name, nullptr),
    m_args(std::move(args))
{
    std::vector<LaxType*> paramsTypes;
    for (auto &arg : m_args)
        paramsTypes.emplace_back(arg.getType());

    _type = new FunctionType(*returnType, paramsTypes);
}

/// Getter for the function arguments
const std::vector<VarSymbol> &FunSymbol::getArgs() {
    return m_args;
}

Symbol::Type FunSymbol::getSymbolType() {
    return FUNCTION;
}

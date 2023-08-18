#include "values/FunctionType.h"

FunctionType::FunctionType(const LaxType& returnType,
    std::vector<LaxType*>&& paramTypes) :
    LaxType(FUNCTION),
    m_returnType(returnType),
    m_params(std::move(paramTypes)) {}

FunctionType::FunctionType(const LaxType& returnType,
    const std::vector<LaxType*>& paramTypes) :
    LaxType(FUNCTION),
    m_returnType(returnType),
    m_params(paramTypes) {}

const std::vector<LaxType*>& FunctionType::getParamTypes() const {
    return m_params;
}

const LaxType& FunctionType::getReturnType() const {
    return m_returnType;
}

bool FunctionType::equals(const LaxType& type) const {
    const auto& t = static_cast<const FunctionType&>(type);
    return LaxType::equals(type) &&
           m_params == t.m_params && m_returnType == t.m_returnType;
}

std::string FunctionType::toString() const {
    std::string string = "(";

    for (const auto& param : m_params)
        string += param->toString() + ",";

    string.pop_back(); // Remove the last comma

    return string + ") -> " + m_returnType.toString();
}

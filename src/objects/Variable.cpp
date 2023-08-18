#include "objects/Variable.h"

/// Class constructor
Variable::Variable(std::unique_ptr<Token> varName, LaxType* type) :
    m_name(std::move(varName)),
    m_type(type) {}

/// Getter for the variable name
Token* Variable::getVarName() const {
    return m_name.get();
}

/// Getter for the variable type
LaxType* Variable::getType() const {
    return m_type;
}

#include "objects/Variable.h"

Variable::Variable(std::unique_ptr<Token> varName, LaxType* type) :
    m_name(std::move(varName)),
    m_type(type) {}

Token* Variable::getVarName() const {
    return m_name.get();
}

LaxType* Variable::getType() const {
    return m_type;
}

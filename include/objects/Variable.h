#ifndef LAX_VARIABLE_H
#define LAX_VARIABLE_H

#include <memory>

#include "tokens/Token.h"

// Forward declarations
class LaxType;

/**
 * Represent a variable
 */
class Variable {
public:
    /**
     * Class constructor
     * @param varName the name of the variable
     * @param type the type of the variable
     */
    Variable(std::unique_ptr<Token> varName, LaxType* type);

    /**
     * Getter for the variable name
     * @return the variable name
     */
    Token* getVarName() const;

    /**
     * Getter for the variable type
     * @return the variable type
     */
    LaxType* getType() const;

private:
    std::unique_ptr<Token> m_name;
    LaxType* m_type;
};

#endif // LAX_VARIABLE_H

#ifndef LAX_VARIABLE_H
#define LAX_VARIABLE_H

#include <memory>

#include "tokens/Token.h"

// Forward declarations
class LaxType;

/**
 * @class Variable
 * @brief Information on a variable in Lax.
 *
 * This class represents a variable in Lax. It is used to store information
 * about the variable, such as its name and type.
 */
class Variable {
public:
    /**
     * @brief Class constructor.
     *
     * Constructs a variable given its name and type. The name is stored as a
     * unique_ptr to a token object.
     *
     * @param varName The name of the variable.
     * @param type The type of the variable.
     */
    Variable(std::unique_ptr<Token> varName, LaxType* type);

    /**
     * @brief Returns the name of the variable.
     * @return The variable name.
     */
    Token* getVarName() const;

    /**
     * @brief Returns the type of the variable.
     * @return The variable type.
     */
    LaxType* getType() const;

private:
    std::unique_ptr<Token> m_name;
    LaxType* m_type;
};

#endif // LAX_VARIABLE_H

#ifndef LAX_FUNNODE_H
#define LAX_FUNNODE_H

#include <memory>
#include <vector>

#include "StmtNode.h"
#include "ast/ASTFwdDecl.h"
#include "tokens/Token.h"

// Forward declarations
class ASTVisitor;
class FunSymbol;
class LaxType;
class ObjString;
class Token;
class Variable;

typedef std::unique_ptr<Token> UToken;
typedef std::unique_ptr<Variable> UVariable;

/**
 * Node for a function definition
 *
 * Declare a function and its definition. A function can take parameters that
 * can be used in its body. A value return type can be specified.
 */
class FunNode : public StmtNode {
public:
    /**
     * Class constructor
     *
     * @param name the function name
     * @param type the function return type
     * @param params the function parameters
     * @param body the function body
     */
    FunNode(UToken token, ObjString* name, LaxType* returnType,
        std::vector<UVariable> params, UBlockNode body);

    /**
	 * Getter for the function token
	 *
	 * @return the token
	 */
    Token* getToken();

    /**
	 * Getter for the function name
	 *
	 * @return the function name
	 */
    ObjString* getName();

    /**
     * Getter for the return type of the function
     *
     * @return the function return type
     */
    LaxType* getReturnType();

    /**
     * Getter for the function body
     *
     * @return the function body
     */
    BlockNode* getBody();

    /**
     * Getter for the list of parameters
     *
     * @return the function parameters
     */
    const std::vector<UVariable>& getParams();

    /**
	 * Getter for the symbol representing the function
	 *
	 * @return a pointer to the symbol
	 */
    FunSymbol* getSymbol();

    /**
     * Setter for the symbol representing the function
     *
     * @param symbol a pointer to the symbol
     */
    void setSymbol(FunSymbol* symbol);

    /**
     * Accept method for the visitor pattern
     */
    void accept(ASTVisitor& visitor) override;

private:
    UToken m_token;
    ObjString* m_name;
    LaxType* m_returnType;
    UBlockNode m_body;
    std::vector<UVariable> m_params;
    FunSymbol* m_symbol;
};

#endif // LAX_FUNNODE_H

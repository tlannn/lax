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
 * @class FunNode
 * @brief Represents a function declaration in the Abstract Syntax Tree (AST).
 *
 * The FunNode class is used to store information about a function. A function
 * is a block of code that can be called from anywhere in the program.
 * It can take arguments and return a value.
 *
 * The function is represented by a symbol in the symbol table. The symbol
 * represents the function name, return type, and parameters.
 */
class FunNode : public StmtNode {
public:

    /**
     * @brief Class constructor.
     * @param token The token representing the function.
     * @param name The name of the function.
     * @param returnType The return type of the function.
     * @param params The list of parameters of the function.
     * @param body The body of the function.
     */
    FunNode(UToken token, ObjString* name, LaxType* returnType,
        std::vector<UVariable> params, UBlockNode body);

    /**
	 * @brief Retrieves the token representing the function.
	 * @return The token representing the function.
	 */
    Token* getToken();

    /**
	 * @brief Retrieves the name of the function.
	 * @return The function name.
	 */
    ObjString* getName();

    /**
     * @brief Retrieves the return type of the function.
     * @return The function return type.
     */
    LaxType* getReturnType();

    /**
     * @brief Retrieves the body of the function.
     * @return The function body.
     */
    BlockNode* getBody();

    /**
     * @brief Retrieves the parameters of the function.
     * @return The function parameters.
     */
    const std::vector<UVariable>& getParams();

    /**
	 * @brief Retrieves the symbol representing the function.
	 * @return The symbol representing the function.
     *
     * @see setSymbol()
	 */
    FunSymbol* getSymbol();

    /**
     * @brief Associates a symbol with this node.
     * @param symbol The symbol to associate with this node.
     *
     * @see getSymbol()
     */
    void setSymbol(FunSymbol* symbol);

    /**
     * @copydoc ASTNode::accept()
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

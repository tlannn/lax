#ifndef LAX_DECLNODE_H
#define LAX_DECLNODE_H

#include <memory>

#include "StmtNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;
class LaxType;
class ObjString;
class Token;
class VarSymbol;

typedef std::shared_ptr<Token> SToken;

/**
 * @class DeclNode
 * @brief Represents a declaration node in the Abstract Syntax Tree (AST).
 *
 * This class encapsulates information about a variable declaration, including
 * the name of the variable, its type, and an optional expression associated
 * with the declaration.
 */
class DeclNode : public StmtNode {
public:
    /**
     * @brief Class constructor.
     *
     * Constructs a new DeclNode object with the provided token, variable name
     * and type, and an optional expression associated with the declaration.
     * A nullptr value can be passed as the expression if no expression is
     * associated with the declaration.
     *
     * @param token The token representing the declaration.
     * @param name The name of the variable being declared.
     * @param type The type of the variable being declared.
     * @param expr The expression associated with the declaration.
     */
    DeclNode(SToken token, ObjString* name, LaxType* type, UExprNode expr);

    /**
     * @brief Retrieves the token associated with this node.
     * @return The token representing the declaration.
     */
    Token* getToken();

    /**
     * @brief Retrieves the name of the variable being declared.
     * @return The variable name.
     */
    ObjString* getName();

    /**
     * @brief Retrieves the type of the variable being declared.
     * @return The variable type.
     */
    LaxType* getType();

    /**
     * @brief Retrieves the expression associated with the declaration.
     * @return The expression associated, or nullptr if no expression is
     * associated.
     */
    ExprNode* getRValue();

    /**
     * @brief Retrieves the symbol associated with the current object.
     * @return The symbol associated with the current object.
     *
     * @see setSymbol()
     */
    VarSymbol* getSymbol();

    /**
     * @brief Sets the symbol associated with the current object.
     * @param symbol The symbol to associate with the current object.
     *
     * @see getSymbol()
     */
    void setSymbol(VarSymbol* symbol);

    /**
     * @copydoc ASTNode::accept()
     */
    void accept(ASTVisitor& visitor) override;

private:
    SToken      m_id;
    ObjString*  m_name;
    LaxType*    m_type;
    UExprNode   m_rvalue;
    VarSymbol*  m_symbol;
};

#endif // LAX_DECLNODE_H

#ifndef LAX_ASSIGNNODE_H
#define LAX_ASSIGNNODE_H

#include <memory>
#include <string>

#include "ExprNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;
class ObjString;
class VarSymbol;

/**
 * @class AssignNode
 * @brief Represents an assignment expression in the Abstract Syntax Tree (AST).
 *
 * The AssignNode class is used to store information about an assignment
 * expression, which assigns the result of an expression to a variable
 * identified by a string.
 */
class AssignNode : public ExprNode {
public:
    /**
     * @brief Class constructor.
     * @param id The identifier of the variable being assigned.
     * @param assignToken The token representing the assignment operator.
     * @param expr The expression being assigned.
     */
    AssignNode(ObjString* identifier, UToken assignToken, UExprNode expr);

    /**
     * @brief Retrieves the identifier associated with this node.
     *
     * This method is used to obtain the identifier of the assigned variable,
     * i.e the variable name. The returned name is represented as a Lax string
     * object.
     *
     * @return The name of the associated with this node.
     */
    ObjString* getVariableName();

    /**
     * @brief Retrieves the expression being assigned for the current object.
     *
     * This function returns the expression assigned to the variable represented
     * by the current object. The expression represents a calculation or equation
     * that is evaluated to produce a value that is assigned to the variable.
     *
     * @return The expression being assigned.
     */
    ExprNode* getExpr();

    /**
     * @brief Returns the symbol associated with the current object.
     *
     * This function retrieves the symbol that represents the variable that is
     * associated with the current object.
     *
     * @return The symbol associated with the current object.
     *
     * @see setSymbol()
     */
    VarSymbol* getSymbol() const;

    /**
     * @brief Sets the symbol of the variable associated with this assignment
     * node.
     * @param symbol The symbol to set.
     *
     * @see getSymbol()
     */
    void setSymbol(VarSymbol* symbol);

    /**
     * @copydoc ASTNode::accept()
     */
    void accept(ASTVisitor& visitor) override;

private:
    ObjString* m_identifier;
    UExprNode  m_expr;
    VarSymbol* m_symbol;
};

#endif // LAX_ASSIGNNODE_H

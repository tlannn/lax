#ifndef LAX_ASSIGNNODE_H
#define LAX_ASSIGNNODE_H

#include <memory>
#include <string>

#include "ExprNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;
class ObjString;
class Token;
class VarSymbol;

typedef std::shared_ptr<Token> SToken;

/**
 * Node for variable assignment statements
 *
 * Assign a new expression, resulting to a single value when reduced, to a
 * variable. The variable must be declared before assignment.
 * The value assigned must match the variable type. If the variable is declared
 * with no specific type, then any value can be assigned. In that case, the
 * variable will take the type of the first value assigned.
 */
class AssignNode : public ExprNode {
public:
    /**
     * Class constructor
     *
     * @param id the identifier of the variable to assign a value to
     * @param assignToken the token of the assignment sign
     * @param expr the expression to assign to the variable
     */
    AssignNode(ObjString* identifier, SToken assignToken, UExprNode expr);

    /**
     * Getter for the token of the variable
     * @return the variable token
     */
    ObjString* getName();

    /**
     * Getter for the new expression assigned
     * @return the expression
     */
    ExprNode* getExpr();

    /**
     * Getter for the symbol representing the variable assigned
     * @return a pointer to the symbol
     */
    VarSymbol* getSymbol() const;

    /**
     * Setter for the symbol representing the variable assigned
     * @param symbol a pointer to the symbol
     */
    void setSymbol(VarSymbol* symbol);

    /**
     * Accept method for the visitor pattern
     */
    void accept(ASTVisitor& visitor) override;

private:
    ObjString* m_identifier;
    UExprNode  m_expr;
    VarSymbol* m_symbol;
};

#endif // LAX_ASSIGNNODE_H

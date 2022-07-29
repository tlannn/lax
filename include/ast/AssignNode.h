#ifndef LAX_ASSIGNNODE_H
#define LAX_ASSIGNNODE_H

#include <memory>

#include "ASTVisitor.h"
#include "Id.h"
#include "ExprNode.h"
#include "StmtNode.h"
#include "tokens/Token.h"

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
	 * @param id the identifier to assign a value to
	 * @param expr the expression to assign to the identifier
	 */
    AssignNode(std::unique_ptr<ExprNode> identifier, std::unique_ptr<ExprNode> expr);

	/**
	 * Getter for the token of the variable
	 * @return the variable token
	 */
	std::string getName();

	/**
	 * Getter for the new expression assigned
	 * @return the expression
	 */
	ExprNode* getExpr();

	/**
	 * Accept method for the visitor pattern
	 */
    void accept(ASTVisitor *visitor) override;

private:
	std::unique_ptr<ExprNode> _identifier;
    std::unique_ptr<ExprNode> _expr;
};

#endif // LAX_ASSIGNNODE_H

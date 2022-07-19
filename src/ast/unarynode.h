#ifndef LAX_UNARYNODE_H
#define LAX_UNARYNODE_H

#include "exprnode.h"

/**
 * Node for unary expressions
 *
 * An unary expression is an operation with a single operand. Only three prefix operators are supported,
 * the negation, the plus and minus sign.
 */
class UnaryNode : public ExprNode {
public:
	/**
	 * Class constructor
	 *
	 * @param op the prefix operator
	 * @param expr the expression associated (the operand)
	 */
	UnaryNode(Token *op, ExprNode *expr);

	/**
	 * Getter for the expression of the operation
	 *
	 * @return the expression
	 */
	ExprNode* getExpr() const;

	/**
	 * Accept method for the visitor pattern
	 */
	void accept(ASTVisitor *visitor) override;

private:
	ExprNode *_expr;
};

#endif //LAX_UNARYNODE_H

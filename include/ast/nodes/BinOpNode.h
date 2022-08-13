#ifndef LAX_BINOPNODE_H
#define LAX_BINOPNODE_H

#include <memory>

#include "ExprNode.h"
#include "ast/NodeTypes.h"

// Forward declarations
class ASTVisitor;
class Token;

typedef std::unique_ptr<Token> UToken;

/**
 * Node for arithmetic expressions in the program, such as basic computes
 *
 * Arithmetic expressions supported are the basic operations addition,
 * subtraction, multiplication and division.
 */
class BinOpNode : public ExprNode {
public:
    /**
     * Class constructor
     *
     * @param left the expression to the left of the operator
     * @param op the token representing the operator
     * @param right the expression to the right of the operator
     */
    BinOpNode(UExprNode left, std::unique_ptr<Token> op, UExprNode right);

    /**
     * Getter for the left expression of the operation
     *
     * @return the left expression
     */
	ExprNode* getLeft();

    /**
     * Getter for the right expression of the operation
     *
     * @return the right expression
     */
	ExprNode* getRight();

	/**
     * Getter for the operator of the operation
     *
     * @return the operator
     */
	Token* getOperator();

    /**
     * Accept method for the visitor pattern
     */
	void accept(ASTVisitor *visitor) override;

protected:
	UExprNode _left;
	UExprNode _right;
	UToken _op;
};

#endif // LAX_BINOPNODE_H

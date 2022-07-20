#ifndef LAX_BINOPNODE_H
#define LAX_BINOPNODE_H

#include <memory>

#include "exprnode.h"
#include "interpreter/astvisitor.h"
#include "tokens/token.h"

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
    BinOpNode(std::unique_ptr<ExprNode> left, std::unique_ptr<Token> op, std::unique_ptr<ExprNode> right);

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
     * Accept method for the visitor pattern
     */
	void accept(ASTVisitor *visitor) override;

protected:
    std::unique_ptr<ExprNode> _left;
	std::unique_ptr<ExprNode> _right;
};

#endif // LAX_BINOPNODE_H

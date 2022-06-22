#ifndef LAX_LOGICALNODE_H
#define LAX_LOGICALNODE_H

#include "exprnode.h"
#include "interpreter/exprvisitor.h"
#include "tokens/token.h"
#include "tokens/type.h"

/**
 * Node for a logical expression
 *
 * The logical expression compares two expressions with an logical AND operator,
 * or a logical OR operator
 */
class LogicalNode : public ExprNode {
public:
    /**
     * Class constructor
     *
     * @param left the expression to the left of the boolean operator
     * @param op the token representing the boolean operator
     * @param right the expression to the right of the boolean operator
     */
    LogicalNode(ExprNode *left, Token op, ExprNode *right);

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
    int accept(ExprVisitor *visitor) override;

protected:
    ExprNode *_left;
    ExprNode *_right;
};

#endif // LAX_LOGICALNODE_H

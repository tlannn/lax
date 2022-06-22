#ifndef LAX_RELATIONALNODE_H
#define LAX_RELATIONALNODE_H

#include "logicalnode.h"
#include "interpreter/exprvisitor.h"
#include "tokens/token.h"
#include "tokens/type.h"

/**
 * Node for an equality or inequality expression
 *
 * The node compares two expressions with compares two expressions with an logical AND operator,
 * or a logical OR operator
 */
class RelationalNode : public LogicalNode {
public:
    /**
     * Class constructor
     *
     * @param left the expression to the left of the boolean operator
     * @param op the token representing the boolean operator
     * @param right the expression to the right of the boolean operator
     */
    RelationalNode(ExprNode *left, Token op, ExprNode *right);

    /**
     * Accept method for the visitor pattern
     */
    int accept(ExprVisitor *visitor) override;
};

#endif // LAX_RELATIONALNODE_H

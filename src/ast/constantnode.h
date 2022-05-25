#ifndef LAX_CONSTANTNODE_H
#define LAX_CONSTANTNODE_H

#include "exprnode.h"
#include "interpreter/exprvisitor.h"
#include "lexer/num.h"
#include "lexer/token.h"
#include "symbols/type.h"

/*
 * Forward declarations for cyclic dependencies
 */
//class ExprVisitor;

/**
 * Node for a constant value.
 *
 * Constants can be numbers, booleans,
 */
class ConstantNode : public ExprNode {
public:
    /**
     * Class constructor
     * @param tok the expression to the left of the operator
     * @param type the token representing the operator
     */
    ConstantNode(Token tok, Type type);

    /**
     * Class constructor
     * @param left the expression to the left of the operator
     * @param op the token representing the operator
     * @param right the expression to the right of the operator
     */
    explicit ConstantNode(int i);

    /**
     * Getter for the value of the constant
     *
     * @return the value
     */
    int getValue();

    /**
     * Accept method for the visitor pattern
     */
    int accept(ExprVisitor *visitor) override;
};

#endif // LAX_CONSTANTNODE_H

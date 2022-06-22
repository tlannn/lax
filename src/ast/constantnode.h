#ifndef LAX_CONSTANTNODE_H
#define LAX_CONSTANTNODE_H

#include "exprnode.h"
#include "interpreter/exprvisitor.h"
#include "tokens/num.h"
#include "tokens/token.h"
#include "tokens/type.h"
#include "tokens/word.h"

/**
 * Node for a constant value.
 *
 * Constants can be numbers, booleans, or any atomic value.
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
     * Getter for the type of the constant
     *
     * @return the type
     */
	Type getType();

    /**
     * Accept method for the visitor pattern
     */
    int accept(ExprVisitor *visitor) override;

private:
	Type _type;
};

#endif // LAX_CONSTANTNODE_H

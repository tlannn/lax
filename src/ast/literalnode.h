#ifndef LAX_LITERALNODE_H
#define LAX_LITERALNODE_H

#include "exprnode.h"
#include "interpreter/exprvisitor.h"
#include "tokens/num.h"
#include "tokens/token.h"
#include "tokens/type.h"
#include "tokens/word.h"

/**
 * Node for a literal value.
 *
 * Literals can be numbers, booleans, or any atomic value.
 */
class LiteralNode : public ExprNode {
public:
    /**
     * Class constructor
     * @param tok the expression to the left of the operator
     * @param type the token representing the operator
     */
    LiteralNode(Token tok, Type type);

    /**
     * Class constructor
     * @param left the expression to the left of the operator
     * @param op the token representing the operator
     * @param right the expression to the right of the operator
     */
    explicit LiteralNode(int i);

    /**
     * Getter for the value of the literal
     *
     * @return the value
     */
    int getValue();

	/**
     * Getter for the type of the literal
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

#endif // LAX_LITERALNODE_H

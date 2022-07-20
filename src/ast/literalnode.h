#ifndef LAX_LITERALNODE_H
#define LAX_LITERALNODE_H

#include <memory>

#include "exprnode.h"
#include "interpreter/astvisitor.h"
#include "tokens/token.h"
#include "tokens/type.h"
#include "tokens/object.h"

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
    LiteralNode(std::unique_ptr<Token> tok, Type type);

    /**
     * Getter for the value of the literal
     *
     * @return the value
     */
    Object getValue();

	/**
     * Getter for the type of the literal
     *
     * @return the type
     */
	Type getType();

    /**
     * Accept method for the visitor pattern
     */
	void accept(ASTVisitor *visitor) override;

private:
	Type _type;
};

#endif // LAX_LITERALNODE_H

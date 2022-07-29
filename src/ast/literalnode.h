#ifndef LAX_LITERALNODE_H
#define LAX_LITERALNODE_H

#include <memory>

#include "astvisitor.h"
#include "exprnode.h"
#include "common/valuetype.h"
#include "common/value.h"
#include "tokens/token.h"

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
    LiteralNode(std::unique_ptr<Token> tok, Value value);

    /**
     * Getter for the value of the literal
     *
     * @return the value
     */
    Value getValue();

	/**
     * Getter for the type of the literal
     *
     * @return the type
     */
//	ValueType getType();
	Token* getToken();

    /**
     * Accept method for the visitor pattern
     */
	void accept(ASTVisitor *visitor) override;

private:
//	ValueType _type;
	std::unique_ptr<Token> _token;
	Value _value;
};

#endif // LAX_LITERALNODE_H

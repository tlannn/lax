#ifndef LAX_LITERALNODE_H
#define LAX_LITERALNODE_H

#include <memory>

#include "ExprNode.h"
#include "ast/ASTFwdDecl.h"
#include "common/Value.h"

// Forward declarations
class ASTVisitor;
class Token;

typedef std::unique_ptr<Token> UToken;

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
    LiteralNode(UToken tok, Value value);

    /**
     * Getter for the value of the literal
     *
     * @return the value
     */
    Value getValue();

    /**
     * Accept method for the visitor pattern
     */
    void accept(ASTVisitor &visitor) override;

private:
	UToken _token;
	Value _value;
};

#endif // LAX_LITERALNODE_H

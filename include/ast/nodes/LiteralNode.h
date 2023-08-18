#ifndef LAX_LITERALNODE_H
#define LAX_LITERALNODE_H

#include <memory>

#include "ExprNode.h"
#include "ast/ASTFwdDecl.h"
#include "values/Value.h"

// Forward declarations
class ASTVisitor;
class Token;

typedef std::shared_ptr<Token> SToken;

/**
 * Node for a literal value.
 *
 * Literals can be numbers, booleans, or any atomic value.
 */
class LiteralNode : public ExprNode {
public:
    /**
     * Class constructor
     * @param token the token representing to literal
     * @param value the value corresponding to the literal
     */
    LiteralNode(SToken token, Value value);

    /**
     * Getter for the value of the literal
     *
     * @return the value
     */
    Value getValue();

    /**
     * Accept method for the visitor pattern
     */
    void accept(ASTVisitor& visitor) override;

private:
    Value m_value;
};

#endif // LAX_LITERALNODE_H

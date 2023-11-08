#ifndef LAX_LITERALNODE_H
#define LAX_LITERALNODE_H

#include <memory>

#include "ExprNode.h"
#include "ast/ASTFwdDecl.h"
#include "values/Value.h"

// Forward declarations
class ASTVisitor;

/**
 * @class LiteralNode
 * @brief Represents a literal in the Abstract Syntax Tree (AST).
 *
 * The LiteralNode class is used to store information about a literal, which is
 * a value that is not identified by a name.
 *
 * The value of the literal is stored as a Lax value object.
 */
class LiteralNode : public ExprNode {
public:
    /**
     * @brief Class constructor.
     * @param token The token representing the literal.
     * @param value The value of the literal.
     */
    LiteralNode(UToken token, Value value);

    /**
     * @brief Retrieves the value associated with this node.
     * @return The value associated with this node.
     */
    Value getValue();

    /**
     * @copydoc ASTNode::accept()
     */
    void accept(ASTVisitor& visitor) override;

private:
    Value m_value;
};

#endif // LAX_LITERALNODE_H

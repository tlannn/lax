#ifndef LAX_LOGICALNODE_H
#define LAX_LOGICALNODE_H

#include <memory>

#include "BinOpNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;
class Token;

typedef std::shared_ptr<Token> SToken;

/**
 * @class LogicalNode
 * @brief Represents a logical expression in the Abstract Syntax Tree (AST).
 *
 * The LogicalNode class is used to store information about a logical expression,
 * which is an expression that evaluates to a boolean value.
 *
 * The node stores the left and right expressions, as well as the token
 * representing the boolean operator.
 *
 * @note The boolean operators supported are AND (&&) and OR (||).
 */
class LogicalNode : public BinOpNode {
public:
    /**
     * @brief Class constructor.
     * @param left The left expression.
     * @param op The token representing the boolean operator.
     * @param right The right expression.
     */
    LogicalNode(UExprNode left, SToken op, UExprNode right);

    /**
     * @copydoc ASTNode::accept()
     */
    void accept(ASTVisitor& visitor) override;
};

#endif // LAX_LOGICALNODE_H

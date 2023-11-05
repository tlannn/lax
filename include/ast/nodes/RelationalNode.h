#ifndef LAX_RELATIONALNODE_H
#define LAX_RELATIONALNODE_H

#include <memory>

#include "LogicalNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;
class Token;

typedef std::shared_ptr<Token> SToken;

/**
 * @class RelationalNode
 * @brief Represents a relational expression in the Abstract Syntax Tree (AST).
 *
 * The RelationalNode class is used to store information about a relational
 * expression, which is an expression that compares two values using mathematical
 * operators. The expression evaluates to a boolean value.
 *
 * The node stores the left and right expressions, as well as the token
 * representing the relational operator.
 *
 * @note The relational operators supported are EQUAL (==), NOT EQUAL (!=),
 * LESS THAN (<), LESS THAN OR EQUAL (<=), GREATER THAN (>), and GREATER THAN
 * OR EQUAL (>=).
 */
class RelationalNode : public LogicalNode {
public:
    /**
     * @brief Class constructor.
     * @param left The left expression.
     * @param op The token representing the relational operator.
     * @param right The right expression.
     */
    RelationalNode(UExprNode left, SToken op, UExprNode right);

    /**
     * @copydoc ASTNode::accept()
     */
    void accept(ASTVisitor& visitor) override;
};

#endif // LAX_RELATIONALNODE_H

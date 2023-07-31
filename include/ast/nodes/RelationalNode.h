#ifndef LAX_RELATIONALNODE_H
#define LAX_RELATIONALNODE_H

#include <memory>

#include "LogicalNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;
class token;

typedef std::unique_ptr<Token> UToken;

/**
 * Node for an equality or inequality expression
 *
 * The node compares two expressions with compares two expressions with an logical AND operator,
 * or a logical OR operator
 */
class RelationalNode : public LogicalNode {
public:
    /**
     * Class constructor
     *
     * @param left the expression to the left of the boolean operator
     * @param op the token representing the boolean operator
     * @param right the expression to the right of the boolean operator
     */
    RelationalNode(UExprNode left, UToken op, UExprNode right);

    /**
     * Accept method for the visitor pattern
     */
	void accept(ASTVisitor &visitor) override;
};

#endif // LAX_RELATIONALNODE_H

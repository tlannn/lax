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
 * Node for a logical expression
 *
 * The logical expression compares two expressions with an logical AND operator,
 * or a logical OR operator
 */
class LogicalNode : public BinOpNode {
public:
    /**
     * Class constructor
     *
     * @param left the expression to the left of the boolean operator
     * @param op the token representing the boolean operator
     * @param right the expression to the right of the boolean operator
     */
    LogicalNode(UExprNode left, SToken op, UExprNode right);

    /**
     * Accept method for the visitor pattern
     */
    void accept(ASTVisitor &visitor) override;
};

#endif // LAX_LOGICALNODE_H

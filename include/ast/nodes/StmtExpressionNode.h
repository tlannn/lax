#ifndef LAX_STMTEXPRESSIONNODE_H
#define LAX_STMTEXPRESSIONNODE_H

#include <memory>

#include "StmtNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;

/**
 * Node for expression statements in the program
 *
 * Expression statements are statements that contains an expression that can be evaluated.
 */
class StmtExpressionNode : public StmtNode {
public:
    /**
     * Class constructor
     *
     * @param expr the expression to visit
     */
    explicit StmtExpressionNode(UExprNode expr);

    /**
     * Getter for the expression to visit
     *
     * @return the expression
     */
	ExprNode* getExpr();

    /**
     * Accept method for the visitor pattern
     */
    void accept(ASTVisitor &visitor) override;

protected:
	UExprNode _expr;
};

#endif // LAX_STMTEXPRESSIONNODE_H

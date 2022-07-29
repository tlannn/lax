#ifndef LAX_STMTEXPRESSIONNODE_H
#define LAX_STMTEXPRESSIONNODE_H

#include <memory>

#include "ASTVisitor.h"
#include "ExprNode.h"
#include "StmtNode.h"

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
    explicit StmtExpressionNode(std::unique_ptr<ExprNode> expr);

    /**
     * Getter for the expression to visit
     *
     * @return the expression
     */
	ExprNode* getExpr();

    /**
     * Accept method for the visitor pattern
     */
    void accept(ASTVisitor *visitor) override;

protected:
	std::unique_ptr<ExprNode> _expr;
};

#endif // LAX_STMTEXPRESSIONNODE_H

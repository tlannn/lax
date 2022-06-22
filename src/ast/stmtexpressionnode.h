#ifndef LAX_STMTEXPRESSIONNODE_H
#define LAX_STMTEXPRESSIONNODE_H

#include "exprnode.h"
#include "stmtnode.h"
#include "interpreter/stmtvisitor.h"

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
     * @param expr the expression to evaluate
     */
    explicit StmtExpressionNode(ExprNode *expr);

    /**
     * Getter for the expression to evaluate
     *
     * @return the expression
     */
    ExprNode* getExpr();

    /**
     * Accept method for the visitor pattern
     */
    void accept(StmtVisitor *visitor) override;

protected:
    ExprNode *_expr;
};

#endif // LAX_STMTEXPRESSIONNODE_H

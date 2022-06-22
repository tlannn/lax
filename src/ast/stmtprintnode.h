#ifndef LAX_STMTPRINTNODE_H
#define LAX_STMTPRINTNODE_H

#include "exprnode.h"
#include "stmtnode.h"
#include "interpreter/stmtvisitor.h"

/**
 * Node for print statements in the program
 *
 * Print statements are statements that print in the console the result of the
 * expression in the statement.
 */
class StmtPrintNode : public StmtNode {
public:
    /**
     * Class constructor
     *
     * @param expr the expression to evaluate and print
     */
    explicit StmtPrintNode(ExprNode *expr);

    /**
     * Getter for the expression to print
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

#endif // LAX_STMTPRINTNODE_H

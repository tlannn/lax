#ifndef LAX_IFNODE_H
#define LAX_IFNODE_H

#include <iostream>

#include "exprnode.h"
#include "stmtnode.h"
#include "interpreter/stmtvisitor.h"

/*
 * Forward declarations for cyclic dependencies
 */
//class StmtVisitor;

/**
 * Node for if statements in the program
 *
 * If statements first evaluate a condition (represented by a boolean expression),
 * and then execute the 'then' statement referenced by the node if the condition
 * is evaluated to true.
 */
class IfNode : public StmtNode {
public:
    /**
     * Class constructor
     *
     * @param expr the expression that conditions whether the 'then' statement
     * will be executed or not
     * @param stmt the statement executed if the condition is evaluated to true
     */
    IfNode(ExprNode *expr, StmtNode *stmt);

    /**
     * Getter for the condition expression
     *
     * @return the conditional expression
     */
    ExprNode* getConditionExpression();

    /**
     * Getter for the 'then' statement
     *
     * @return the 'then' statement
     */
    StmtNode* getThenStatement();

    /**
     * Accept method for the visitor pattern
     */
    void accept(StmtVisitor *visitor) override;

protected:
    ExprNode *_expr;
    StmtNode *_stmt;
};

#endif // LAX_IFNODE_H

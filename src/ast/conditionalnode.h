#ifndef LAX_CONDITIONALNODE_H
#define LAX_CONDITIONALNODE_H

#include "exprnode.h"
#include "stmtnode.h"
#include "interpreter/astvisitor.h"

/**
 * Node for if/else statements in the program
 *
 * If/else statements first visit a condition (represented by a boolean expression),
 * and then execute the 'then' statement referenced by the node if the condition
 * is evaluated to true. Otherwise, the 'else' statement referenced is executed if
 * there is one.
 */
class ConditionalNode : public StmtNode {
public:
    /**
     * Class constructor
     *
     * @param expr the expression that conditions whether the 'then' statement
     * will be executed or not
     * @param thenSmt the statement executed if the condition is evaluated to true
     * @param elseStmt the statement executed if the condition is evaluated to false
     */
    ConditionalNode(ExprNode *expr, StmtNode *thenStmt, StmtNode *elseStmt);

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
     * Getter for the 'else' statement
     *
     * @return the 'else' statement
     */
    StmtNode* getElseStatement();

    /**
     * Accept method for the visitor pattern
     */
    void accept(ASTVisitor *visitor) override;

protected:
    ExprNode *_expr;
    StmtNode *_thenStmt;
    StmtNode *_elseStmt;
};

#endif // LAX_CONDITIONALNODE_H

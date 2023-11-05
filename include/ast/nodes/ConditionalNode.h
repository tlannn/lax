#ifndef LAX_CONDITIONALNODE_H
#define LAX_CONDITIONALNODE_H

#include "StmtNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;
class ExprNode;

/**
 * @class ConditionalNode
 * @brief Represents a conditional statement node in the Abstract Syntax
 * Tree (AST).
 *
 * The ConditionalNode class is used to store information about a conditional
 * statement, which is a statement that executes a statement if a condition is
 * evaluated to true, or another statement if the condition is evaluated to
 * false.
 *
 * Conditional statements are used to control the flow of execution of a program.
 * They are also known as if-else statements, because they usually take the form
 * of an if statement followed by an else statement.
 */
class ConditionalNode : public StmtNode {
public:
    /**
     * @brief Class constructor.
     *
     * Constructs a new ConditionalNode object with the provided expression,
     * then statement, and else statement.
     *
     * @param expr The expression used as a condition.
     * @param thenSmt The statement executed if the condition is evaluated to
     * true.
     * @param elseStmt The statement executed if the condition is evaluated to
     * false.
     */
    ConditionalNode(UExprNode expr, UStmtNode thenStmt, UStmtNode elseStmt);

    /**
     * @brief Returns the conditional expression.
     *
     * This function returns the expression used as a condition to determine
     * which statement to execute.
     *
     * @return The conditional expression.
     */
    ExprNode* getConditionExpression();

    /**
     * @brief Returns the statement node for the then branch.
     *
     * This functions returns the statement node that is executed if the
     * condition is evaluated to true.
     *
     * @return The statement node for the then branch.
     */
    StmtNode* getThenStatement();


    /**
     * @brief Returns the statement node for the else branch.
     *
     * This functions returns the statement node that is executed if the
     * condition is evaluated to false.
     *
     * @return The statement node for the else branch.
     */
    StmtNode* getElseStatement();

    /**
     * @copydoc ASTNode::accept()
     */
    void accept(ASTVisitor& visitor) override;

protected:
    UExprNode m_expr;
    UStmtNode m_thenStmt;
    UStmtNode m_elseStmt;
};

#endif // LAX_CONDITIONALNODE_H

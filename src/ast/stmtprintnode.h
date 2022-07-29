#ifndef LAX_STMTPRINTNODE_H
#define LAX_STMTPRINTNODE_H

#include <memory>

#include "astvisitor.h"
#include "exprnode.h"
#include "stmtnode.h"

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
     * @param expr the expression to visit and print
     */
    explicit StmtPrintNode(std::unique_ptr<ExprNode> expr);

    /**
     * Getter for the expression to print
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

#endif // LAX_STMTPRINTNODE_H

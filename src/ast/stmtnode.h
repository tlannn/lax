#ifndef LAX_STMTNODE_H
#define LAX_STMTNODE_H

#include "astvisitor.h"
#include "astnode.h"
#include "tokens/token.h"

/**
 * Node for statements in the program
 *
 * Statements express an action to execute. This can be an expression, an assignment, etc.
 * Statements can't be reduced to a value, since their purpose is only to execute actions.
 */
class StmtNode : public ASTNode {
public:
    /**
     * Class constructor
     */
    StmtNode() = default;

    /**
     * Accept method for the visitor pattern
     */
    void accept(ASTVisitor *visitor) override;
};

#endif // LAX_STMTNODE_H

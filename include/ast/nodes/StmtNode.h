#ifndef LAX_STMTNODE_H
#define LAX_STMTNODE_H

#include <memory>

#include "ASTNode.h"

// Forward declarations
class ASTVisitor;

/**
 * @class StmtNode
 * @brief Represents a statement in the Abstract Syntax Tree (AST).
 *
 * This class serves as a base class for statement nodes in the AST.
 *
 * Statements are used to represent statements in the source code, such as
 * variable declarations, function definitions, and control flow statements.
 *
 * These statements are executed for their side effects. They do not evaluate to
 * a value, in contrast to expressions.
 *
 * @see ExprNode
 */
class StmtNode : public ASTNode {
public:
    /**
     * @brief Class constructor.
     *
     * Default constructor.
     */
    StmtNode() = default;

    /**
     * @copydoc ASTNode::accept()
     */
    void accept(ASTVisitor& visitor) override;
};

#endif // LAX_STMTNODE_H

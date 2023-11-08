#ifndef LAX_EXPRNODE_H
#define LAX_EXPRNODE_H

#include <memory>

#include "ASTNode.h"
#include "tokens/Token.h"

// Forward declarations
class ASTVisitor;

/**
 * @class ExprNode
 * @brief Represents an expression in an Abstract Syntax Tree (AST).
 *
 * This class serves as a base class for expression nodes in the AST.
 *
 * Each node is associated with a token that represents an operand or an
 * operator in the expression. The token is used to determine the position of
 * the node in the source code, as the token stores the line number and column
 * number where the expression begins. This information is used to report errors
 * in the source code.
 *
 * The ExprNode class is used to store information about an expression, which is
 * a combination of operators and operands. It is used to represent the root
 * node of an expression, with the operands and operators represented by the
 * children of the node which are also ExprNode objects.
 *
 * Expressions typically represent values, such as literals or variables. They
 * are also used to represent operations on these values, such as arithmetic
 * operations, logical operations, and function calls, that are evaluated to
 * produce a value.
 *
 * ExprNodes are necessarily part of StmtNodes, which are used to represent
 * statements. Statements are the instructions that make up a program, and
 * expressions are used to represent values, which are used in statements.
 *
 * @see StmtNode
 */
class ExprNode : public ASTNode {
public:
    /**
     * @brief Class constructor.
     * @param token The token representing the expression.
     */
    explicit ExprNode(UToken token);

    /**
     * @brief Retrieves the token associated with this node.
     * @return The token associated with this node.
     */
    Token* getToken();

    /**
     * @copydoc ASTNode::accept()
     */
    void accept(ASTVisitor& visitor) override;

protected:
    UToken m_token;
};

#endif // LAX_EXPRNODE_H

#ifndef LAX_BINOPNODE_H
#define LAX_BINOPNODE_H

#include <memory>

#include "ExprNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;

/**
 * @class BinOpNode
 * @brief Represents a binary operation node in an Abstract Syntax Tree (AST).
 *
 * The BinOpNode class stores information about a binary operation, such as
 * arithmetic operations.
 *
 * A binary operation is an operation that has two operands, such as addition,
 * subtraction, multiplication, and division. The operands are represented by
 * the left and right children of the node.
 *
 * @note The binary operators supported are addition (+), subtraction (-),
 * multiplication (*) and division (/).
 */
class BinOpNode : public ExprNode {
public:
    /**
     * @brief Class constructor.
     *
     * Constructs a new BinOpNode object with the provided left and right
     * operands and the operator token. Both operands are represented by
     * expression nodes, which are stored as children of the current node.
     *
     * @param left The left operand of the operation.
     * @param op The token representing the operator.
     * @param right The right operand of the operation.
     */
    BinOpNode(UExprNode left, UToken op, UExprNode right);

    /**
     * @brief Retrieves the left child of the node.
     * @return The left child node, or nullptr if it does not exist.
     */
    ExprNode* getLeft();

    /**
     * @brief Retrieves the right child of the node.
     * @return The right child node, or nullptr if it does not exist.
     */
    ExprNode* getRight();

    /**
     * @copydoc ASTNode::accept()
     */
    void accept(ASTVisitor& visitor) override;

protected:
    UExprNode m_left;
    UExprNode m_right;
};

#endif // LAX_BINOPNODE_H

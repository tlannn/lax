#ifndef LAX_UNARYNODE_H
#define LAX_UNARYNODE_H

#include <memory>

#include "ExprNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;
class Token;

typedef std::shared_ptr<Token> SToken;

/**
 * @class UnaryNode
 * @brief Represents a unary expression in the Abstract Syntax Tree (AST).
 *
 * The UnaryNode class is used to store information about a unary expression,
 * which is an expression that has a single operand. It is used to represent
 * unary operators, such as the logical negation operator and the unary minus
 * operator.
 */
class UnaryNode : public ExprNode {
public:
	/**
     * @brief Class constructor.
     * @param op The token representing the operator.
     * @param expr The expression representing the operand.
     */
	UnaryNode(SToken op, UExprNode expr);

	/**
     * @brief Retrieves the operator associated with this node.
     * @return The operator associated with this node.
     */
	ExprNode* getExpr() const;

	/**
	 * @copydoc ASTNode::accept()
	 */
	void accept(ASTVisitor &visitor) override;

private:
	UExprNode m_expr;
};

#endif //LAX_UNARYNODE_H

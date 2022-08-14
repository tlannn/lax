#ifndef LAX_WHILENODE_H
#define LAX_WHILENODE_H

#include "StmtNode.h"
#include "ast/NodeTypes.h"

// Forward declarations
class ASTVisitor;

class WhileNode : public StmtNode {
public:
	/**
	 * Class constructor.
	 *
	 * @param cond the condition expression.
	 * @param body the body of the loop.
	 */
	WhileNode(UExprNode cond, UStmtNode body);

	/**
	 * Getter for the expression to evaluate as a condition to continue the loop.
	 * @return the condition expression.
	 */
	ExprNode* getConditionExpression();

	/**
	 * Getter for the body of the loop.
	 * @return the body.
	 */
	StmtNode* getBody();

	/// Accept method for the visitor pattern.
	void accept(ASTVisitor *visitor) override;

private:
	UExprNode _cond;
	UStmtNode _body;
};

#endif //LAX_WHILENODE_H

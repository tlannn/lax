#ifndef LAX_FORLOOPNODE_H
#define LAX_FORLOOPNODE_H

#include <vector>

#include "StmtNode.h"
#include "ast/NodeTypes.h"

// Forward declarations
class ASTVisitor;

/**
 * Node for a for-loop.
 *
 * The for-loop is composed of a header and a body. The latter contains the
 * statements to execute as long as a condition is true. The former is divided
 * in three parts :
 * - the initialization, where the loop variant is defined ;
 * - the condition to check before each iteration of the loop ;
 * - the iteration expression which is executed after every iteration of the loop.
 */
class ForLoopNode : public StmtNode {
public:
	/**
	 * Class constructor.
	 *
	 * @param init the list of initializations.
	 * @param cond the condition expression.
	 * @param iter the increment expression.
	 * @param body the body of the loop.
	 */
	ForLoopNode(std::vector<UStmtNode> init, UExprNode cond, UExprNode iter, UStmtNode body);

	/**
	 * Getter for the statements in the initialization part of the loop header.
	 * @return the initializer statements.
	 */
	const std::vector<UStmtNode>& getInitializers();

	/**
	 * Getter for the expression to evaluate as a condition to continue the loop.
	 * @return the condition expression.
	 */
	ExprNode* getConditionExpression();

	/**
	 * Getter for the expression executed after every iteration.
	 * @return the iteration expression.
	 */
	ExprNode* getIterationExpression();

	/**
	 * Getter for the body of the loop.
	 * @return the body.
	 */
	StmtNode* getBody();

	/// Accept method for the visitor pattern.
	void accept(ASTVisitor *visitor) override;

private:
	std::vector<UStmtNode> _init;
	UExprNode _cond;
	UExprNode _iter;
	UStmtNode _body;
};

#endif //LAX_FORLOOPNODE_H

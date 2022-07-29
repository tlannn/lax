#ifndef LAX_CALLNODE_H
#define LAX_CALLNODE_H

#include <memory>
#include <vector>

#include "astvisitor.h"
#include "exprnode.h"

/**
 * Node for a function call
 *
 * Call a function and execute the statements in its body. If the function
 * expects parameters, then values specified during the call are passed to the
 * function in the same order as they appear.
 * The function must be declared and defined before it can be called.
 */
class CallNode : public ExprNode {
public:
	/**
	 * Class constructor
	 *
	 * @param callee the expression that is called
	 * @param tok the closing parenthesis token
	 * @param args the list of arguments
	 */
	CallNode(std::unique_ptr<ExprNode> callee, std::unique_ptr<Token> tok, std::vector<std::unique_ptr<ExprNode>> args);

	/**
	 * Getter for the callee
	 *
	 * @return the callee
	 */
	ExprNode* getCallee();

	/**
	 * Getter for the arguments of the call
	 *
	 * @return the arguments
	 */
	const std::vector<std::unique_ptr<ExprNode>>& getArgs();

	/**
	 * Accept method for the visitor pattern
	 */
	void accept(ASTVisitor *visitor) override;

private:
	std::unique_ptr<ExprNode> _callee;
	std::unique_ptr<Token> _paren;
	std::vector<std::unique_ptr<ExprNode>> _args;
};

#endif // LAX_CALLNODE_H

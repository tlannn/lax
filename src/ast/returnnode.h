#ifndef LAX_RETURNNODE_H
#define LAX_RETURNNODE_H

#include <memory>

#include "astvisitor.h"
#include "exprnode.h"
#include "stmtnode.h"
#include "tokens/token.h"

class ReturnNode : public StmtNode {
public:
	/**
	 * Class constructor
	 * @param returnToken the token of the return keyword
	 * @param value the expression returned
	 */
	ReturnNode(std::unique_ptr<Token> returnToken, std::unique_ptr<ExprNode> value);

	/**
	 * Getter for the return keyword token
	 * @return the return token
	 */
	Token* getToken();

	/**
	 * Getter for the expression returned
	 * @return the expression
	 */
	ExprNode* getValue();

	/**
	 * Accept method for the visitor pattern
	 */
	void accept(ASTVisitor *visitor) override;

private:
	std::unique_ptr<Token> _returnToken;
	std::unique_ptr<ExprNode> _value;
};


#endif // LAX_RETURNNODE_H

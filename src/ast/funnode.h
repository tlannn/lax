#ifndef LAX_FUNNODE_H
#define LAX_FUNNODE_H

#include <memory>
#include <vector>

#include "blocknode.h"
#include "common/valuetype.h"
#include "objects/variable.h"
#include "tokens/token.h"

/**
 * Node for a function definition
 *
 * Declare a function and its definition. A function can take parameters that
 * can be used in its body. A value return type can be specified.
 */
class FunNode : public StmtNode {
public:
	/**
	 * Class constructor
	 *
	 * @param name the function name
	 * @param type the function return type
	 * @param params the function parameters
	 * @param body the function body
	 */
	FunNode(std::unique_ptr<Token> name, ValueType type,
			std::vector<std::unique_ptr<Variable>> params, std::unique_ptr<BlockNode> body);

	/**
	 * Getter for the return type of the function
	 *
	 * @return the function return type
	 */
	ValueType getType();

	/**
	 * Getter for the function name
	 *
	 * @return the function name
	 */
	Token* getName();

	/**
	 * Getter for the function body
	 *
	 * @return the function body
	 */
	BlockNode* getBody();

	/**
	 * Getter for the list of parameters
	 *
	 * @return the function parameters
	 */
	const std::vector<std::unique_ptr<Variable>>& getParams();

	/**
	 * Accept method for the visitor pattern
	 */
	void accept(ASTVisitor *visitor) override;

private:
	ValueType _type;
	std::unique_ptr<Token> _name;
	std::unique_ptr<BlockNode> _body;
	std::vector<std::unique_ptr<Variable>> _params;
};

#endif // LAX_FUNNODE_H

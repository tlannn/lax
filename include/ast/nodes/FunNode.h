#ifndef LAX_FUNNODE_H
#define LAX_FUNNODE_H

#include <memory>
#include <vector>

#include "StmtNode.h"
#include "ast/ASTFwdDecl.h"
#include "common/ValueType.h"
#include "tokens/Token.h"

// Forward declarations
class ASTVisitor;
class Token;
class Variable;

typedef std::unique_ptr<Token> UToken;
typedef std::unique_ptr<Variable> UVariable;

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
	FunNode(UToken name, ValueType type,
			std::vector<UVariable> params, UBlockNode body);

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
	const std::vector<UVariable>& getParams();

	/**
	 * Accept method for the visitor pattern
	 */
	void accept(ASTVisitor &visitor) override;

private:
	ValueType _type;
	UToken _name;
	UBlockNode _body;
	std::vector<UVariable> _params;
};

#endif // LAX_FUNNODE_H

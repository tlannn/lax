#ifndef LAX_ID_H
#define LAX_ID_H

#include <memory>

#include "ASTVisitor.h"
#include "ExprNode.h"
#include "tokens/Token.h"

/**
 * Node for an identifier
 *
 * An identifier represents a variable name. Whenever it appears in the code,
 * it is replaced by the current value of the variable defined by this
 * identifier.
 */
class Id : public ExprNode {
public:
	/**
	 * Class constructor
	 *
	 * @param name the name defining the identifier
	 */
    explicit Id(std::unique_ptr<Token> name);

	/**
	 * Getter for the name of the identifier
	 *
	 * @return the name
	 */
	Token* getName();

	/**
	 * Accept method for the visitor pattern
	 */
	void accept(ASTVisitor *visitor) override;

private:
	std::unique_ptr<Token> _name;
};

#endif // LAX_ID_H

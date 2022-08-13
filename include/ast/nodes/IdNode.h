#ifndef LAX_IDNODE_H
#define LAX_IDNODE_H

#include <memory>

#include "ExprNode.h"

// Forward declarations
class ASTVisitor;
class Token;

typedef std::unique_ptr<Token> UToken;

/**
 * Node for an identifier
 *
 * An identifier represents a variable name. Whenever it appears in the code,
 * it is replaced by the current value of the variable defined by this
 * identifier.
 */
class IdNode : public ExprNode {
public:
	/**
	 * Class constructor
	 *
	 * @param name the name defining the identifier
	 */
    explicit IdNode(UToken name);

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
	UToken _name;
};

#endif // LAX_IDNODE_H

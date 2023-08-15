#ifndef LAX_EXPRNODE_H
#define LAX_EXPRNODE_H

#include <memory>

#include "ASTNode.h"
#include "tokens/Token.h"

// Forward declarations
class ASTVisitor;
class Token;

typedef std::shared_ptr<Token> SToken;

/**
 * Node for expressions in the program
 *
 * Expressions can be reduced to a single value. It is a combination of one or
 * more constants, operators, etc.
 */
class ExprNode : public ASTNode {
public:
    /**
     * Class constructor
     */
    explicit ExprNode(SToken token);

	/**
	 * Getter for the token of the node
	 * @return the token
	 */
	Token* getToken();

    /**
     * Accept method for the visitor pattern
     */
    void accept(ASTVisitor &visitor) override;

protected:
	SToken _token;
};

#endif // LAX_EXPRNODE_H

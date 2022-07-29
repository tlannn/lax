#ifndef LAX_ASTNODE_H
#define LAX_ASTNODE_H

#include "ASTVisitor.h"
#include "tokens/Token.h"

/**
 * Base node for the Abstract Syntax Tree
 */
class ASTNode {
public:
	/**
	 * Class constructor
	 */
//	ASTNode(Token *token);
	ASTNode() = default;

	/**
	 * Class destructor
	 */
	virtual ~ASTNode() = default;

	/**
	 * Getter for the token of the node
	 * @return the token
	 */
//	Token* getToken();

	/**
	 * Accepts an *ASTVisitor* and call its visit method corresponding to
     * the type of the node
     *
     * @param visitor the visitor that wants to visit the node
	 */
	virtual void accept(ASTVisitor *visitor) = 0;

protected:
//	Token *_token;
};

#endif // LAX_ASTNODE_H

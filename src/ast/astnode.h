#ifndef LAX_ASTNODE_H
#define LAX_ASTNODE_H

#include "interpreter/astvisitor.h"

/**
 * Base node for the Abstract Syntax Tree
 */
class ASTNode {
public:
	/**
	 * Class constructor
	 */
	ASTNode() = default;

	/**
	 * Accepts an *ASTVisitor* and call its visit method corresponding to
     * the type of the node
     *
     * @param visitor the visitor that wants to visit the node
	 */
	virtual void accept(ASTVisitor *visitor) = 0;
};

#endif // LAX_ASTNODE_H

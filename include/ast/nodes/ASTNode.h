#ifndef LAX_ASTNODE_H
#define LAX_ASTNODE_H

// Forward declarations
class ASTVisitor;
class Scope;

/**
 * Base node for the Abstract Syntax Tree
 */
class ASTNode {
public:
	/**
	 * Class constructor
	 */
	ASTNode();

	/**
	 * Class destructor
	 */
	virtual ~ASTNode() = default;

    /**
     * Getter for the scope of the node
     * @return the scope
     */
    Scope* getScope();

    /**
     * Setter for the scope of the node
     * @param scope the scope
     */
    void setScope(Scope *scope);

	/**
	 * Accepts an *ASTVisitor* and call its visit method corresponding to
     * the type of the node
     *
     * @param visitor the visitor that wants to visit the node
	 */
	virtual void accept(ASTVisitor &visitor) = 0;

private:
    Scope *m_scope;
};

#endif // LAX_ASTNODE_H

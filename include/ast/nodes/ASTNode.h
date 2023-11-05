#ifndef LAX_ASTNODE_H
#define LAX_ASTNODE_H

// Forward declarations
class ASTVisitor;
class Scope;

/**
 * @class ASTNode
 * @brief Represents an Abstract Syntax Tree (AST) node.
 *
 * This class serves as a base class for all types of nodes in the AST. Each
 * node can have children nodes and may contain information such as the type of
 * the node and the value associated with the node.
 */
class ASTNode {
public:
    /**
     * @brief Class constructor.
     */
    ASTNode();

    /**
     * @brief Class destructor.
     *
     * This class provides a default implementation for the destructor
     * ~ASTNode().
     *
     * @note If no explicit destructor is provided in the derived classes, this
     * default destructor will be used.
     */
    virtual ~ASTNode() = default;

    /**
     * @brief Returns the scope of the current object.
     *
     * The scope represents the accessibility of the object within a particular
     * context. For example, if the object is defined within a class,
     * the scope can indicate whether the object is private, public, or
     * protected.
     *
     * @return The scope of the current object.
     *
     * @see setScope()
     */
    Scope* getScope();

    /**
     * @brief Assigns the provided scope to the current object.
     * @param scope The scope to assign to the current object.
     *
     * @see getScope()
     */
    void setScope(Scope* scope);

    /**
     * @brief Accepts a visitor and allows it to visit the object implementing
     * this class.
     *
     * This pure virtual function should be implemented by any class that wants
     * to be visited by an ASTVisitor object. By accepting a visitor, the object
     * can provide access to its internal structure for analysis or
     * transformation.
     *
     * @param visitor The ASTVisitor object that will visit the implementing
     * object.
     *
     * @note Implementing classes should define their own accept() function
     * according to their specific needs.
     * @note The visitor argument should be passed to the accept() function of
     * the underlying structure that needs to be visited.
     *
     * @see ASTVisitor
     */
    virtual void accept(ASTVisitor& visitor) = 0;

private:
    Scope* m_scope;
};

#endif // LAX_ASTNODE_H

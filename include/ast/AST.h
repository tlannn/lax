#ifndef LAX_AST_H
#define LAX_AST_H

#include <memory>

#include "ast/nodes/ASTNode.h"

// Forward declarations
class ASTVisitor;

/**
 * Abstract Syntax Tree (AST) representation. Controls the root node
 * and provides methods of traversal and access to the root node.
 */
class AST {
public:
    /**
     * Class constructor.
     * @param root the root node of the AST.
     */
    explicit AST(std::unique_ptr<ASTNode> root);

    /// Class destructor.
    ~AST() = default;

    /**
     * Traverses the AST starting from root node using the provided visitor.
     * @param visitor Reference to ASTVisitor object.
     */
    void traverse(ASTVisitor& visitor);

    /**
     * Provides a reference to root node.
     * @return Reference to root ASTNode.
     */
    ASTNode& getRoot() const;

private:
    std::unique_ptr<ASTNode> m_root;
};

#endif //LAX_AST_H

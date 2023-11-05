#ifndef LAX_AST_H
#define LAX_AST_H

#include <memory>

#include "ast/nodes/ASTNode.h"

// Forward declarations
class ASTVisitor;

/**
 * @class AST
 * @brief Represents an Abstract Syntax Tree (AST).
 *
 * This class encapsulates information about an Abstract Syntax Tree (AST).
 * It is used to store the root node of the AST and provides methods of
 * traversal and access to the root node.
 *
 * The AST is a tree representation of the source code. It is used to store
 * information about the program and is used by the interpreter to execute
 * the program.
 *
 * The AST is constructed by the parser. The parser traverses the source code
 * and constructs the AST by creating nodes for each statement, expression,
 * and declaration.
 */
class AST {
public:
    /**
     * @brief Class constructor.
     *
     * Constructs an AST with the provided root node.
     *
     * @param root The root node of the AST.
     */
    explicit AST(std::unique_ptr<ASTNode> root);

    /**
     * @brief Class destructor.
     *
     * Default destructor.
     */
    ~AST() = default;

    /**
     * @brief Traverses the AST.
     *
     * Traverses the AST using the provided visitor, starting at the root node.
     *
     * @param visitor The visitor used to traverse the AST.
     */
    void traverse(ASTVisitor& visitor);

    /**
     * @brief Retrieves the root node of the AST.
     * @return The root node.
     */
    ASTNode& getRoot() const;

private:
    std::unique_ptr<ASTNode> m_root;
};

#endif //LAX_AST_H

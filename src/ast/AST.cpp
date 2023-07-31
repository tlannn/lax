#include "ast/AST.h"
#include "ast/ASTVisitor.h"
#include "ast/nodes/ASTNode.h"

/// Class constructor.
AST::AST(std::unique_ptr<ASTNode> root) : m_root(std::move(root)) {}

/// Traverses the AST starting from root node using the provided visitor.
void AST::traverse(ASTVisitor &visitor) {
    m_root->accept(visitor);
}

/// Provides a reference to root node.
ASTNode &AST::getRoot() const {
    return *m_root;
}

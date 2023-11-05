#include "ast/AST.h"
#include "ast/ASTVisitor.h"
#include "ast/nodes/ASTNode.h"

AST::AST(std::unique_ptr<ASTNode> root) : m_root(std::move(root)) {}

void AST::traverse(ASTVisitor& visitor) {
    m_root->accept(visitor);
}

ASTNode& AST::getRoot() const {
    return *m_root;
}

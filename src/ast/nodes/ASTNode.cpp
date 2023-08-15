#include "ast/nodes/ASTNode.h"

ASTNode::ASTNode() : m_scope(nullptr) {}

Scope* ASTNode::getScope() {
    return m_scope;
}

void ASTNode::setScope(Scope *scope) {
    m_scope = scope;
}

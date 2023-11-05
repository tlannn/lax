#ifndef LAX_BLOCKNODE_H
#define LAX_BLOCKNODE_H

#include <memory>

#include "StmtNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;
class SeqNode;

/**
 * @class BlockNode
 * @brief Represents a block of statements in an Abstract Syntax Tree (AST).
 *
 * A BlockNode is a type of node that contains a sequence of nodes. It acts as a
 * container for other nodes and provides the ability to manipulate and
 * traverse them. A BlockNode typically defines a new scope for inner variables,
 * so a new Scope object must be created for each BlockNode.
 */
class BlockNode : public StmtNode {
public:
    /**
     * @brief Class constructor.
     * @param seq The sequence of nodes enclosed in this block.
     */
    explicit BlockNode(USeqNode seq);

    /**
     * @brief Retrieves the sequence of nodes contained in this block.
     * @return The sequence of nodes.
     */
    SeqNode* getSequence();

    /**
     * @copydoc ASTNode::accept()
     */
    void accept(ASTVisitor& visitor) override;

private:
    USeqNode m_seq;
};

#endif // LAX_BLOCKNODE_H

#ifndef LAX_BLOCKNODE_H
#define LAX_BLOCKNODE_H

#include <memory>

#include "StmtNode.h"
#include "ast/NodeTypes.h"

// Forward declarations
class ASTVisitor;
class SeqNode;

/**
 * Node for blocks of statements
 *
 * A block is delimited by braces, inside which one or multiple statements are
 * present. The statements are represented by a sequence of statements.
 */
class BlockNode : public StmtNode {
public:
	/**
     * Class constructor
     *
     * @param stmts the statements to execute inside the block
     */
    explicit BlockNode(USeqNode seq);

	/**
	 * Getter for the sequence of statements inside the block
	 *
	 * @return the sequence
	 */
	SeqNode* getSequence();

	/**
     * Accept method for the visitor pattern
     */
    void accept(ASTVisitor *visitor) override;

private:
	USeqNode _seq;
};

#endif // LAX_BLOCKNODE_H

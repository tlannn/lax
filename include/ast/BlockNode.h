#ifndef LAX_BLOCKNODE_H
#define LAX_BLOCKNODE_H

#include <memory>

#include "ASTVisitor.h"
#include "StmtNode.h"
#include "SeqNode.h"

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
    explicit BlockNode(std::unique_ptr<SeqNode> seq);

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
	std::unique_ptr<SeqNode> _seq;
};

#endif // LAX_BLOCKNODE_H

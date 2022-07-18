#ifndef LAX_BLOCKNODE_H
#define LAX_BLOCKNODE_H

#include <vector>

#include "stmtnode.h"
#include "seqnode.h"
#include "interpreter/astvisitor.h"

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
    explicit BlockNode(SeqNode* seq);

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
    SeqNode* _seq;
};

#endif // LAX_BLOCKNODE_H

#ifndef LAX_BLOCKNODE_H
#define LAX_BLOCKNODE_H

#include <vector>

#include "stmtnode.h"
#include "interpreter/stmtvisitor.h"

/**
 * Node for blocks of statements
 *
 * A block is delimited by braces, inside which one or multiple statements are
 * present. Each statement is executed one after the other.
 */
class BlockNode : public StmtNode {
public:
	/**
     * Class constructor
     *
     * @param stmts the statements to execute inside the block
     */
    explicit BlockNode(std::vector<StmtNode*> stmts);

	/**
	 * Getter for the statements inside the block
	 *
	 * @return the statements
	 */
    std::vector<StmtNode*> getStatements();

	/**
     * Accept method for the visitor pattern
     */
    void accept(StmtVisitor *visitor) override;

private:
    std::vector<StmtNode*> _stmts;
};

#endif // LAX_BLOCKNODE_H

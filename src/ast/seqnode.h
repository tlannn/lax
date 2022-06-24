#ifndef LAX_SEQNODE_H
#define LAX_SEQNODE_H

#include <vector>

#include "stmtnode.h"

/**
 * Node for a sequence of statements to execute one after the other
 */
class SeqNode : public StmtNode {
public:
	/**
	 * SeqNode constructor
	 *
	 * @param stmts the statements to execute
	 */
	SeqNode(std::vector<StmtNode*> stmts);

	/**
	 * Getter for the statements to execute
	 *
	 * @return the statements
	 */
	std::vector<StmtNode*> getStatements();

	/**
     * Accept method for the visitor pattern
     */
	void accept(StmtVisitor *visitor);

private:
	std::vector<StmtNode*> _stmts;
};

#endif // LAX_SEQNODE_H

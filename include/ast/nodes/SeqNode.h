#ifndef LAX_SEQNODE_H
#define LAX_SEQNODE_H

#include <memory>
#include <vector>

#include "StmtNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;

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
	explicit SeqNode(std::vector<UStmtNode> stmts);

	/**
	 * Getter for the statements to execute
	 *
	 * @return the statements
	 */
	const std::vector<UStmtNode>& getStatements();

	/**
     * Accept method for the visitor pattern
     */
	void accept(ASTVisitor &visitor) override;

private:
	std::vector<UStmtNode> _stmts;
};

#endif // LAX_SEQNODE_H

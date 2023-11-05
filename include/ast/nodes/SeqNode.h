#ifndef LAX_SEQNODE_H
#define LAX_SEQNODE_H

#include <memory>
#include <vector>

#include "StmtNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;

/**
 * @class SeqNode
 * @brief Represents a sequence of statements in the Abstract Syntax Tree (AST).
 *
 * The SeqNode class is used to store information about a sequence of statements.
 * A sequence of statements is used to execute multiple statements in a row.
 */
class SeqNode : public StmtNode {
public:
    /**
     * @brief Class constructor.
     * @param stmts The statements to execute.
     */
    explicit SeqNode(std::vector<UStmtNode> stmts);

    /**
     * @brief Retrieves the statements to execute.
     * @return The statements to execute.
     */
    const std::vector<UStmtNode>& getStatements();

    /**
     * @copydoc ASTNode::accept()
     */
    void accept(ASTVisitor& visitor) override;

private:
    std::vector<UStmtNode> m_stmts;
};

#endif // LAX_SEQNODE_H

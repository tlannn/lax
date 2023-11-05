#ifndef LAX_RETURNNODE_H
#define LAX_RETURNNODE_H

#include <memory>

#include "StmtNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;
class Token;

typedef std::unique_ptr<Token> UToken;

/**
 * @class ReturnNode
 * @brief Represents a return statement in the Abstract Syntax Tree (AST).
 *
 * The ReturnNode class is used to store information about a return statement.
 * A return statement is used to return a value from a function.
 *
 * The node stores the token representing the return keyword, as well as the
 * expression returned.
 */
class ReturnNode : public StmtNode {
public:
    /**
     * @brief Class constructor.
     * @param returnToken The token representing the return keyword.
     * @param value The expression returned.
     */
    ReturnNode(UToken returnToken, UExprNode value);

    /**
     * @brief Retrieves the token representing the return keyword.
     * @return The token representing the return keyword.
     */
    Token* getToken();

    /**
     * @brief Retrieves the expression returned.
     * @return The expression returned.
     */
    ExprNode* getValue();

    /**
     * @copydoc ASTNode::accept()
     */
    void accept(ASTVisitor& visitor) override;

private:
    UToken m_returnToken;
    UExprNode m_value;
};

#endif // LAX_RETURNNODE_H

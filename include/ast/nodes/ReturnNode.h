#ifndef LAX_RETURNNODE_H
#define LAX_RETURNNODE_H

#include <memory>

#include "StmtNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;
class Token;

typedef std::unique_ptr<Token> UToken;

class ReturnNode : public StmtNode {
public:
    /**
     * Class constructor
     * @param returnToken the token of the return keyword
     * @param value the expression returned
     */
    ReturnNode(UToken returnToken, UExprNode value);

    /**
     * Getter for the return keyword token
     * @return the return token
     */
    Token* getToken();

    /**
     * Getter for the expression returned
     * @return the expression
     */
    ExprNode* getValue();

    /**
     * Accept method for the visitor pattern
     */
    void accept(ASTVisitor& visitor) override;

private:
    UToken m_returnToken;
    UExprNode m_value;
};

#endif // LAX_RETURNNODE_H

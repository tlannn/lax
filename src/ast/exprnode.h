#ifndef LAX_EXPRNODE_H
#define LAX_EXPRNODE_H

#include "astnode.h"
#include "interpreter/astvisitor.h"
#include "tokens/token.h"

/**
 * Node for expressions in the program
 *
 * Expressions can be reduced to a single value. It is a combination of one or
 * more constants, operators, etc.
 */
class ExprNode : public ASTNode {
public:
    /**
     * Class constructor
     * @param tok the token in the expression
     * @param type the type of the expression
     */
    explicit ExprNode(Token *tok);

    /**
     * Getter for the token
     *
     * @return the token
     */
    Token* getToken();

    /**
     * Accept method for the visitor pattern
     */
    void accept(ASTVisitor *visitor) override;

protected:
    Token *_tok;
};

#endif // LAX_EXPRNODE_H

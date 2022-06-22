#ifndef LAX_EXPRNODE_H
#define LAX_EXPRNODE_H

#include "astnode.h"
#include "interpreter/exprvisitor.h"
#include "tokens/token.h"
#include "tokens/type.h"

/*
 * Forward declarations for cyclic dependencies
 */
class ExprVisitor;

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
    ExprNode(Token tok);

    /**
     * Getter for the token
     *
     * @return the token
     */
    Token getToken();

    /**
     * Abstract accept method for the visitor pattern
     *
     * Accepts an *ExprVisitor* and call its visit method corresponding to
     * the type of the node
     *
     * @param visitor the visitor that wants to visit the node
     * @return the reduced value of the expression
     */
    virtual int accept(ExprVisitor *visitor) = 0;

protected:
    Token _tok;
};

#endif // LAX_EXPRNODE_H

#ifndef LAX_EXPRVISITOR_H
#define LAX_EXPRVISITOR_H

/*
 * Forward declarations to avoid cyclic dependencies
 */
class ExprNode;
class BinOpNode;
class ConstantNode;
class LogicalNode;
class RelationalNode;

/**
 * Visitor interface for expressions
 */
class ExprVisitor {
public:
    /**
     * Evaluate an expression node and return the value to which it has been reduced
     *
     * @param node the expression node to evaluate
     * @return the reduced value of the expression
     */
    virtual int evaluate(ExprNode *node) = 0;

    /**
     * Visit a BinOpNode and compute the operation represented by the node
     *
     * @param node the node to visit
     * @return the result of the operation
     */
    virtual int visit(BinOpNode *node) = 0;

    /**
     * Visit a ConstantNode and return the constant value represented
     *
     * @param node the node to visit
     * @return the constant value
     */
    virtual int visit(ConstantNode *node) = 0;

    /**
     * Visit a LogicalNode and compute the boolean value of the node expression
     *
     * @param node the node to visit
     * @return the boolean value
     */
    virtual int visit(LogicalNode *node) = 0;

    /**
     * Visit a RelationalNode and compute the boolean value of the equality (or inequality) expression
     *
     * @param node the node to visit
     * @return the boolean value
     */
    virtual int visit(RelationalNode *node) = 0;
};

#endif // LAX_EXPRVISITOR_H

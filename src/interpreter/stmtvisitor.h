#ifndef LAX_STMTVISITOR_H
#define LAX_STMTVISITOR_H

/*
 * Forward declarations to avoid cyclic dependencies
 */
class StmtNode;
class StmtExpressionNode;
class StmtPrintNode;
class IfNode;

/**
 * Visitor interface for statements
 */
class StmtVisitor {
public:
    /**
     * Execute a statement node
     *
     * @param the node representing the statement to execute
     */
    virtual void execute(StmtNode *node) = 0;

    /**
     * Visit a StmtExpressionNode node and compute the expression in the statement
     *
     * @param node the node to visit
     */
    virtual void visit(StmtExpressionNode *node) = 0;

    /**
     * Visit a StmtPrintNode node and print the result of the expression in the statement
     *
     * @param node the node to visit
     */
    virtual void visit(StmtPrintNode *node) = 0;

    /**
     * Visit an IfNode and execute the statement referenced if the condition
     * is evaluated to true
     *
     * @param node the node to visit
     */
    virtual void visit(IfNode *node) = 0;
};

#endif // LAX_STMTVISITOR_H

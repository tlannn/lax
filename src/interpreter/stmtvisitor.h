#ifndef LAX_STMTVISITOR_H
#define LAX_STMTVISITOR_H

/*
 * Forward declarations to avoid cyclic dependencies
 */
class StmtNode;
class StmtExpressionNode;
class StmtPrintNode;
class ConditionalNode;
class DeclNode;
class AssignNode;
class BlockNode;

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
     * Visit an ConditionalNode and execute the statement referenced if the condition
     * is evaluated to true
     *
     * @param node the node to visit
     */
    virtual void visit(ConditionalNode *node) = 0;

	/**
     * Visit a DeclNode and declare a variable
     *
     * @param node the node to visit
     */
    virtual void visit(DeclNode *node) = 0;

	/**
     * Visit an AssignNode and assign a new value to a variable
     *
     * @param node the node to visit
     */
    virtual void visit(AssignNode *node) = 0;

	/**
     * Visit a BlockNode and execute all the statements inside the block
     *
     * @param node the node to visit
     */
    virtual void visit(BlockNode *node) = 0;
};

#endif // LAX_STMTVISITOR_H

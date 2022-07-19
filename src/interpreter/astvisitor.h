#ifndef LAX_ASTVISITOR_H
#define LAX_ASTVISITOR_H

/*
 * Forward declarations to avoid cyclic dependencies
 */
class ASTNode;
class ExprNode;
class BinOpNode;
class Id;
class LiteralNode;
class LogicalNode;
class RelationalNode;
class UnaryNode;

class StmtNode;
class StmtExpressionNode;
class StmtPrintNode;
class ConditionalNode;
class DeclNode;
class AssignNode;
class BlockNode;
class SeqNode;

/**
 * Visitor interface
 */
class ASTVisitor {
public:
	/**
	 * Evaluate an expression node and return the value to which it has been reduced
	 *
	 * @param node the expression node to visit
	 * @return the reduced value of the expression
	 */
	virtual void visit(ExprNode *node) = 0;

	/**
	 * Visit a BinOpNode and compute the operation represented by the node
	 *
	 * @param node the node to visit
	 * @return the result of the operation
	 */
	virtual void visit(BinOpNode *node) = 0;

	/**
	 * Visit a LogicalNode and compute the boolean value of the node expression
	 *
	 * @param node the node to visit
	 * @return the boolean value
	 */
	virtual void visit(LogicalNode *node) = 0;

	/**
	 * Visit a RelationalNode and compute the boolean value of the equality (or inequality) expression
	 *
	 * @param node the node to visit
	 * @return the boolean value
	 */
	virtual void visit(RelationalNode *node) = 0;

	/**
     * Visit a LiteralNode and return the literal value represented
     *
     * @param node the node to visit
     * @return the literal value
     */
	virtual void visit(LiteralNode *node) = 0;

	/**
     * Visit an Id (identifier) and return the value of the variable defined with this identifier
     *
     * @param node the node to visit
     * @return the value of the variable
     */
	virtual void visit(Id *node) = 0;

	/**
     * Visit an unary expression and return the literal value
     *
     * @param node the node to visit
     * @return the literal value
     */
	virtual void visit(UnaryNode *node) = 0;

	/**
     * Execute a statement node
     *
     * @param the node representing the statement to execute
     */
	virtual void visit(StmtNode *node) = 0;

	/**
     * Visit a BlockNode and execute the sequence of statements inside it
     *
     * @param node the node to visit
     */
	virtual void visit(BlockNode *node) = 0;

	/**
     * Visit a SeqNode and execute all the statements inside it
     *
     * @param node the node to visit
     */
	virtual void visit(SeqNode *node) = 0;

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
     * Visit an ConditionalNode and execute the statement referenced if the condition
     * is evaluated to true
     *
     * @param node the node to visit
     */
	virtual void visit(ConditionalNode *node) = 0;

	/**
	 * Visit a StmtPrintNode node and print the result of the expression in the statement
	 *
	 * @param node the node to visit
	 */
	virtual void visit(StmtPrintNode *node) = 0;

	/**
     * Visit a StmtExpressionNode node and compute the expression in the statement
     *
     * @param node the node to visit
     */
	virtual void visit(StmtExpressionNode *node) = 0;
};

#endif //LAX_ASTVISITOR_H

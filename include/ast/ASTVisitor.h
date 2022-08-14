#ifndef LAX_ASTVISITOR_H
#define LAX_ASTVISITOR_H

// Forward declarations
class ASTNode;
class AssignNode;
class BinOpNode;
class BlockNode;
class CallNode;
class ConditionalNode;
class DeclNode;
class ExprNode;
class ForLoopNode;
class FunNode;
class IdNode;
class LiteralNode;
class LogicalNode;
class RelationalNode;
class ReturnNode;
class SeqNode;
class StmtExpressionNode;
class StmtNode;
class UnaryNode;
class WhileLoopNode;

/**
 * Visitor interface
 */
class ASTVisitor {
public:
	/**
	 * Visit an ExprNode
	 *
	 * @param node the node to visit
	 */
	virtual void visit(ExprNode *node) = 0;

	/**
     * Visit an AssignNode
     *
     * @param node the node to visit
     */
	virtual void visit(AssignNode *node) = 0;

	/**
	 * Visit a LogicalNode
	 *
	 * @param node the node to visit
	 */
	virtual void visit(LogicalNode *node) = 0;

	/**
	 * Visit a RelationalNode
	 *
	 * @param node the node to visit
	 */
	virtual void visit(RelationalNode *node) = 0;

	/**
	 * Visit a BinOpNode
	 *
	 * @param node the node to visit
	 */
	virtual void visit(BinOpNode *node) = 0;

	/**
     * Visit an UnaryNode
     *
     * @param node the node to visit
     */
	virtual void visit(UnaryNode *node) = 0;

	/**
     * Visit a CallNode
     *
     * @param node the node to visit
     */
	virtual void visit(CallNode *node) = 0;

	/**
     * Visit a LiteralNode
     *
     * @param node the node to visit
     */
	virtual void visit(LiteralNode *node) = 0;

	/**
     * Visit an IdNode
     *
     * @param node the node to visit
     */
	virtual void visit(IdNode *node) = 0;

	/**
     * Visit a StmtNode
     *
     * @param the node to visit
     */
	virtual void visit(StmtNode *node) = 0;

	/**
     * Visit a BlockNode
     *
     * @param node the node to visit
     */
	virtual void visit(BlockNode *node) = 0;

	/**
     * Visit a SeqNode
     *
     * @param node the node to visit
     */
	virtual void visit(SeqNode *node) = 0;

	/**
     * Visit a DeclNode
     *
     * @param node the node to visit
     */
	virtual void visit(DeclNode *node) = 0;

	/**
     * Visit a ConditionalNode
     *
     * @param node the node to visit
     */
	virtual void visit(ConditionalNode *node) = 0;

	/**
     * Visit a WhileNode
     *
     * @param node the node to visit
     */
	virtual void visit(WhileLoopNode *node) = 0;

	/**
     * Visit a ForNode
     *
     * @param node the node to visit
     */
	virtual void visit(ForLoopNode *node) = 0;

	/**
     * Visit a FunNode
     *
     * @param node the node to visit
     */
	virtual void visit(FunNode *node) = 0;

	/**
     * Visit a ReturnNode
     *
     * @param node the node to visit
     */
	virtual void visit(ReturnNode *node) = 0;

	/**
     * Visit a StmtExpressionNode
     *
     * @param node the node to visit
     */
	virtual void visit(StmtExpressionNode *node) = 0;
};

#endif //LAX_ASTVISITOR_H

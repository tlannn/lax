#ifndef LAX_ASTVISITOR_H
#define LAX_ASTVISITOR_H

#include "ast/ASTFwdDecl.h"

/**
 * @class ASTVisitor
 * @brief Interface for visiting nodes in an Abstract Syntax Tree (AST).
 *
 * The ASTVisitor class is an interface for visiting nodes in an AST. It
 * provides a visit method for each type of node in the AST. The visitor is used
 * to traverse the AST and perform operations on each node.
 */
class ASTVisitor {
public:
    /**
     * @brief Visits an ExprNode.
     * @param node The node to visit.
     */
    virtual void visit(ExprNode& node) = 0;

    /**
     * @brief Visits an AssignNode.
     * @param node The node to visit.
     */
    virtual void visit(AssignNode& node) = 0;

    /**
     * @brief Visits a LogicalNode.
     * @param node The node to visit.
     */
    virtual void visit(LogicalNode& node) = 0;

    /**
     * @brief Visits a RelationalNode.
     * @param node The node to visit.
     */
    virtual void visit(RelationalNode& node) = 0;

    /**
     * @brief Visits a BinOpNode.
     * @param node The node to visit.
     */
    virtual void visit(BinOpNode& node) = 0;

    /**
     * @brief Visits an UnaryNode.
     * @param node The node to visit.
     */
    virtual void visit(UnaryNode& node) = 0;

    /**
     * @brief Visits a CallNode.
     * @param node The node to visit.
     */
    virtual void visit(CallNode& node) = 0;

    /**
     * @brief Visits a LiteralNode.
     * @param node The node to visit.
     */
    virtual void visit(LiteralNode& node) = 0;

    /**
     * @brief Visits an IdNode.
     * @param node The node to visit.
     */
    virtual void visit(IdNode& node) = 0;

    /**
     * @brief Visits a StmtNode.
     * @param The node to visit.
     */
    virtual void visit(StmtNode& node) = 0;

    /**
     * @brief Visits a BlockNode.
     * @param node The node to visit.
     */
    virtual void visit(BlockNode& node) = 0;

    /**
     * @brief Visits a SeqNode.
     * @param node The node to visit.
     */
    virtual void visit(SeqNode& node) = 0;

    /**
     * @brief Visits a DeclNode.
     * @param node The node to visit.
     */
    virtual void visit(DeclNode& node) = 0;

    /**
     * @brief Visits a ConditionalNode.
     * @param node The node to visit.
     */
    virtual void visit(ConditionalNode& node) = 0;

    /**
     * @brief Visits a FunNode.
     * @param node The node to visit.
     */
    virtual void visit(FunNode& node) = 0;

    /**
     * @brief Visits a ReturnNode.
     * @param node The node to visit.
     */
    virtual void visit(ReturnNode& node) = 0;

    /**
     * @brief Visits a StmtExpressionNode.
     * @param node The node to visit.
     */
    virtual void visit(StmtExpressionNode& node) = 0;
};

#endif //LAX_ASTVISITOR_H

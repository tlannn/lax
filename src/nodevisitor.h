#ifndef NODEVISITOR_H
#define NODEVISITOR_H

#include "ast.h"

/*
 * Forward declarations for cyclic dependencies
 */
class Expr;
class BinOpNode;
class ConstantNode;
class Stmt;
class StmtExpression;
class StmtPrint;
class IfNode;

/**
 * Visitor interface for expressions
 */
class ExprVisitor {
    public:
        /*
         * Evaluate an expression node and return the value to which it has been reduced
         *
         * @param node the expression node to evaluate
         * @return the reduced value of the expression
         */
        virtual int evaluate(Expr *node) = 0;

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
};

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
        virtual void execute(Stmt *node) = 0;

        /**
         * Visit a StmtExpression node and compute the expression in the statement
         *
         * @param node the node to visit
         */
        virtual void visit(StmtExpression *node) = 0;

        /**
         * Visit a StmtPrint node and print the result of the expression in the statement
         *
         * @param node the node to visit
         */
        virtual void visit(StmtPrint *node) = 0;

        /**
         * Visit an IfNode and execute the statement referenced if the condition
         * is evaluated to true
         *
         * @param node the node to visit
         */
        virtual void visit(IfNode *node) = 0;
};

#endif

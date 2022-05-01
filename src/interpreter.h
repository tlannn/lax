#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>

#include "ast.h"
#include "nodevisitor.h"
#include "parser.h"

/**
 * Interpreter for the Lax language
 *
 * Implements the ExprVisitor and StmtVisitor visitor interfaces.
 * The role of the interpreter is to visit an Abstract Syntax Tree and simulate
 * the excution of the program represented. It defines methods that describe how
 * nodes of an AST must be handled.
 */
class Interpreter : public ExprVisitor, StmtVisitor {
    public:
        /**
         * Class constructor
         *
         * @param parser
         */
        Interpreter(Parser parser);

        /// Interpret the program parsed by the parser
        void interpret();

        /// Evaluate an expression node and return the value to which it has been reduced
        int evaluate(Expr *node);

        /// Visit a BinOpNode and compute the operation represented by the node
        int visit(BinOpNode *node);

        /// Visit a ConstantNode and return the constant value represented
        int visit(ConstantNode *node);

        /// Execute a statement node
        void execute(Stmt *node);

        /// Visit a StmtExpression node and compute the expression in the statement
        void visit(StmtExpression *node);

        /// Visit a StmtPrint node and print the result of the expression in the statement
        void visit(StmtPrint *node);

        /// Visit an IfNode and execute the statement referenced if the condition
        /// is evaluated to true
        void visit(IfNode *node);

    private:
        Parser _parser;
};

#endif

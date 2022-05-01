#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>

#include "token.h"
#include "nodevisitor.h"

/*
 * Forward declarations for cyclic dependencies
 */
class ExprVisitor;
class StmtVisitor;

/**
 * Base node of the Abstract Syntax Tree
 */
class ASTNode {};

/**
 * Node for expressions in the program
 *
 * Expressions can be reduced to a single value. It is a combination of one or
 * more constants, operators, etc.
 */
class Expr : public ASTNode {
    public:
        /**
         * Class constructor
         * @param tok the token in the expression
         * @param type the type of the expression
         */
        Expr(Token tok, Type type);

        /**
         * Getter for the token
         *
         * @return the token
         */
        Token getToken();

        /**
         * Getter for the type of the expression
         *
         * @return the type of the expression
         */
        Type getType();

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
        Type _type;
};

/**
 * Node for arithmetic expressions in the program, such as basic computes
 *
 * Arithmetic expressions supported are the basic operations addition,
 * subtraction, multiplication and division.
 */
class BinOpNode : public Expr {
    public:
        /**
         * Class constructor
         *
         * @param left the expression to the left of the operator
         * @param op the token representing the operator
         * @param right the expression to the right of the operator
         */
        BinOpNode(Expr *left, Token op, Expr *right);

        /**
         * Getter for the left expression of the operation
         *
         * @return the left expression
         */
        Expr* getLeft();

        /**
         * Getter for the right expression of the operation
         *
         * @return the right expression
         */
        Expr* getRight();

        /**
         * Accept method for the visitor pattern
         */
        int accept(ExprVisitor *visitor);

    protected:
        Expr *_left;
        Expr *_right;
};

/**
 * Node for a constant value.
 *
 * Constants can be numbers, booleans,
 */
class ConstantNode : public Expr {
    public:
        /**
         * Class constructor
         * @param tok the expression to the left of the operator
         * @param type the token representing the operator
         */
        ConstantNode(Token tok, Type type);

        /**
         * Class constructor
         * @param left the expression to the left of the operator
         * @param op the token representing the operator
         * @param right the expression to the right of the operator
         */
        ConstantNode(int i);

        /**
         * Getter for the value of the constant
         *
         * @return the value
         */
        int getValue();

        /**
         * Accept method for the visitor pattern
         */
        int accept(ExprVisitor *visitor);
};

/**
 * Node for statements in the program
 *
 * Statements express an action to execute. This can be an expression, an assignment, etc.
 * Statements can't be reduced to a value, since their purpose is only to execute actions.
 */
class Stmt : public ASTNode {
    public:
        /**
         * Class constructor
         */
        Stmt() {}

        /**
         * Accept method for the visitor pattern
         */
        virtual void accept(StmtVisitor *visitor) = 0;
};

/**
 * Node for expression statements in the program
 *
 * Expression statements are statements that contains an expression that can be evaluated.
 */
class StmtExpression : public Stmt {
    public:
        /**
         * Class constructor
         *
         * @param expr the expression to evaluate
         */
        StmtExpression(Expr *expr);

        /**
         * Getter for the expression to evaluate
         *
         * @return the expression
         */
        Expr* getExpr();

        /**
         * Accept method for the visitor pattern
         */
        void accept(StmtVisitor *visitor);

    protected:
        Expr *_expr;
};

/**
 * Node for print statements in the program
 *
 * Print statements are statements that print in the console the result of the
 * expression in the statement.
 */
class StmtPrint : public Stmt {
    public:
        /**
         * Class constructor
         *
         * @param expr the expression to evaluate and print
         */
        StmtPrint(Expr *expr);

        /**
         * Getter for the expression to print
         *
         * @return the expression
         */
        Expr* getExpr();

        /**
         * Accept method for the visitor pattern
         */
        void accept(StmtVisitor *visitor);

    protected:
        Expr *_expr;
};

/**
 * Node for if statements in the program
 *
 * If statements first evaluate a condition (represented by a boolean expression),
 * and then execute the 'then' statement referenced by the node if the condition
 * is evaluated to true.
 */
class IfNode : public Stmt {
    public:
        /**
         * Class constructor
         *
         * @param expr the expression that conditions whether the 'then' statement
         * will be executed or not
         * @param stmt the statement executed if the condition is evaluated to true
         */
        IfNode(Expr *expr, Stmt *stmt);

        /**
         * Getter for the condition expression
         *
         * @return the conditional expression
         */
        Expr* getConditionExpression();

        /**
         * Getter for the 'then' statement
         *
         * @return the 'then' statement
         */
        Stmt* getThenStatement();

        /**
         * Accept method for the visitor pattern
         */
        void accept(StmtVisitor *visitor);

    protected:
        Expr *_expr;
        Stmt *_stmt;
};

#endif

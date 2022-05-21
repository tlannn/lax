#include "ast.h"

/**
 * Expr class definition
 */

/// Expr constructor
Expr::Expr(Token tok, Type type) : _tok(tok), _type(type) {}

/// Getter for the operator
Token Expr::getToken() {
    return _tok;
}

/// Getter for the type of the expression
Type Expr::getType() {
    return _type;
}


/**
 * BinOpNode class definition
 */

/// BinOpNode constructor
BinOpNode::BinOpNode(Expr *left, Token op, Expr *right) : Expr(op, Type::INT), _left(left), _right(right) {}

/// Getter for the left expression of the operation
Expr* BinOpNode::getLeft() {
    return _left;
}

/// Getter for the right expression of the operation
Expr* BinOpNode::getRight() {
    return _right;
}

/// Accept method for the visitor pattern
int BinOpNode::accept(ExprVisitor *visitor) {
    return visitor->visit(this);
}


/**
 * ConstantNode class definition
 */

/// ConstantNode constructor
ConstantNode::ConstantNode(Token tok, Type type) : Expr(tok, type) {}

/// ConstantNode constructor
ConstantNode::ConstantNode(int i) : Expr(Num(i), Type::INT) {}

/// Getter for the value of the constant
int ConstantNode::getValue() {
    if (_type == Type::INT)
        return stoi(_tok.toString());
    else if (_type == Type::BOOL)
        return _tok.toString() == Word::TRUE.toString() ? 1 : 0;

    return -1;
}

/// Accept method for the visitor pattern
int ConstantNode::accept(ExprVisitor *visitor) {
    return visitor->visit(this);
}

/**
 * LogicalNode class definition
 */

/// LogicalNode constructor
LogicalNode::LogicalNode(Expr *left, Token op, Expr *right) : Expr(op, check(left->getType(), right->getType())), _left(left), _right(right) {}

/// Getter for the left expression of the boolean operation
Expr* LogicalNode::getLeft() {
    return _left;
}

/// Getter for the right expression of the boolean operation
Expr* LogicalNode::getRight() {
    return _right;
}

/// Accept method for the visitor pattern
int LogicalNode::accept(ExprVisitor *visitor) {
    return visitor->visit(this);
}

/// Check if the expression can result in a boolean expression
Type LogicalNode::check(Type t1, Type t2) {
    if (t1 != Type::BOOL) return t1;
    else if (t2 != Type::BOOL) return t2;
    else return Type::BOOL;
}

/**
 * EqualityNode class definition
 */

/// EqualityNode constructor
RelationalNode::RelationalNode(Expr *left, Token op, Expr *right) : LogicalNode(left, op, right) {
    // Override logical node type check logic
    _type = check(left->getType(), right->getType());
}

/// Accept method for the visitor pattern
int RelationalNode::accept(ExprVisitor *visitor) {
    return visitor->visit(this);
}

/// Check if the expression can result in a boolean expression
Type RelationalNode::check(Type t1, Type t2) {
    if (t1 == t2) return Type::BOOL;
    else if (t1 != Type::BOOL) return t1;
    else return t2;
}

/**
 * StmtExpression class definition
 */

/// StmtExpression constructor
StmtExpression::StmtExpression(Expr *expr) : _expr(expr) {}

/// Getter for the expression to evaluate
Expr* StmtExpression::getExpr() {
    return _expr;
}

/// Accept method for the visitor pattern
void StmtExpression::accept(StmtVisitor *visitor) {
    visitor->visit(this);
}


/**
 * StmtPrint class definition
 */

 /// StmtPrint constructor
StmtPrint::StmtPrint(Expr *expr) : _expr(expr) {}

/// Getter for the expression to print
Expr* StmtPrint::getExpr() {
    return _expr;
}

/// Accept method for the visitor pattern
void StmtPrint::accept(StmtVisitor *visitor) {
    visitor->visit(this);
}


/**
 * IfNode class definition
 */

/// IfNode constructor
IfNode::IfNode(Expr *expr, Stmt *stmt) : _expr(expr), _stmt(stmt) {
    if (expr->getType() != Type::BOOL)
        std::cout << "boolean required in if" << std::endl;
}

/// Getter for the condition expression
Expr* IfNode::getConditionExpression() {
    return _expr;
}

/// Getter for the 'then' statement
Stmt* IfNode::getThenStatement() {
    return _stmt;
}

/// Accept method for the visitor pattern
void IfNode::accept(StmtVisitor *visitor) {
    visitor->visit(this);
}

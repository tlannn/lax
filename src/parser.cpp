#include "parser.h"
using namespace std;

/// Class constructor
Parser::Parser(Lexer lex) : _lex(lex) {}

/// Parse the following source code until a complete statement is read. The statement
/// is represented by a node in the syntax tree
Stmt* Parser::parse() {
    move();
    return stmt();
}

/// Read the next token in the source code
void Parser::move() {
    _look = _lex.nextToken();
}

/// Check if the type of the current token is the same as the type expected
bool Parser::check(int tokenType) {
    if (_look->getType() == tokenType) return true;
    else return false;
}

/// Check the type of the current token, and if it is the same as the type
/// expected, read the next token
void Parser::match(int tokenType) {
    if (_look->getType() == tokenType) move();
    else throw std::runtime_error("unexpected character " + to_string(_look->getType()));
}

/// Build a node representing an expression
Expr* Parser::expr() {
    Expr *expr = term();

    while (_look->toString() == "+" || _look->toString() == "-") {
        Token op = *_look;
        move();
        expr = new BinOpNode(expr, op, term());
    }

    return expr;
}

/// Build a node representing a term
Expr* Parser::term() {
    Expr *expr = factor();

    while (_look->toString() == "*" || _look->toString() == "/") {
        Token op = *_look;
        move();
        expr = new BinOpNode(expr, op, factor());
    }

    return expr;
}

/// Build a node representing a factor
Expr* Parser::factor() {
    Expr *expr;

    switch (_look->getType()) {
        case TokenType::LPAREN: {
            move();
            expr = Parser::expr();
            match(TokenType::RPAREN);
            break;
        }
        case TokenType::NUM: {
            expr = new ConstantNode(*_look, Type::INT);
            move();
            break;
        }
        case TokenType::TRUE:
        case TokenType::FALSE: {
            expr = new ConstantNode(*_look, Type::BOOL);
            move();
            break;
        }
    }

    return expr;
}

/// Build a node representing a statement
Stmt* Parser::stmt() {
    if (check(TokenType::IF)) {
        move();
        return ifStmt();
    }

    else if (check(TokenType::PRINT)) {
        move();
        return printStmt();
    }

    return expressionStmt();
}

/// Build a node representing an expression statement
Stmt* Parser::expressionStmt() {
    Expr *expr = Parser::expr();
    match(TokenType::SEMICOL);

    return new StmtExpression(expr);
}

/// Build a node representing a print statement
Stmt* Parser::printStmt() {
    Expr *expr = Parser::expr();
    match(TokenType::SEMICOL);

    return new StmtPrint(expr);
}

/// Build a node representing an if statement
Stmt* Parser::ifStmt() {
    match(TokenType::LPAREN);
    Expr *condition = Parser::expr();
    match(TokenType::RPAREN);

    Stmt *then = Parser::stmt();

    return new IfNode(condition, then);
}

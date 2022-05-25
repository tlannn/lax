#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "ast/exprnode.h"
#include "ast/binopnode.h"
#include "ast/constantnode.h"
#include "ast/logicalnode.h"
#include "ast/relationalnode.h"
#include "ast/ifnode.h"
#include "ast/stmtnode.h"
#include "ast/stmtexpressionnode.h"
#include "ast/stmtprintnode.h"
#include "lexer/lexer.h"
#include "lexer/token.h"

/**
 * Parser for the Lax language
 *
 * The parser reads a stream of tokens and constructs a syntax tree. Tokens are
 */
class Parser {
public:
    /**
     * Class constructor
     *
     * @param lex the lexical analyzer used to read the source code
     */
    explicit Parser(Lexer &lex);

    /**
     * Parse the following source code until a complete statement is read. The statement
     * is represented by a node in the syntax tree
     *
     * @return the statement node created
     */
    StmtNode* parse();

private:
    /// Read the next token in the source code
    void move();

    /**
     * Check if the type of the current token is the same as the type expected
     *
     * @param tokenType the type expected
     * @return true if the types are the same
     */
    bool check(int tokenType);

    /**
     * Check the type of the current token, and if it is the same as the type
     * expected, read the next token
     *
     * @param tokenType the type expected
     *
     * @throws std::runtime_error when the expected token type is different
     * from the current token type
     */
    void match(int tokenType);

    /**
     * Build a node representing a logical OR expression
     *
     * @return the node created
     */
    ExprNode* logic();

    /**
     * Build a node representing a logical AND expression
     *
     * @return the node created
     */
    ExprNode* join();

    /**
     * Build a node representing an equality or inequality expression
     *
     * @return the node created
     */
    ExprNode* rel();

    /**
     * Build a node representing an expression
     *
     * @return the node created
     */
    ExprNode* expr();

    /**
     * Build a node representing a term
     *
     * @return the node created
     */
    ExprNode* term();

    /**
     * Build a node representing a factor
     *
     * @return the node created
     */
    ExprNode* factor();

    /**
     * Build a node representing a statement
     *
     * @return the node created
     */
    StmtNode* stmt();

    /**
     * Build a node representing an expression statement
     *
     * @return the node created
     */
    StmtNode* expressionStmt();

    /**
     * Build a node representing a print statement
     *
     * @return the node created
     */
    StmtNode* printStmt();

    /**
     * Build a node representing an if statement
     *
     * @return the node created
     */
    StmtNode* ifStmt();

    Lexer _lex; // The lexical analyzer
    Token *_look; // The lookahead token
};

#endif

#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "parseerror.h"
#include "ast/exprnode.h"
#include "ast/assignnode.h"
#include "ast/binopnode.h"
#include "ast/blocknode.h"
#include "ast/literalnode.h"
#include "ast/declnode.h"
#include "ast/id.h"
#include "ast/logicalnode.h"
#include "ast/relationalnode.h"
#include "ast/conditionalnode.h"
#include "ast/stmtnode.h"
#include "ast/stmtexpressionnode.h"
#include "ast/stmtprintnode.h"
#include "ast/unarynode.h"
#include "tokens/token.h"
#include "lexer/lexer.h"
#include "symbols/varsymbol.h"
#include "symbols/env.h"
#include "utils/logger.h"

/**
 * Parser for the Lax language
 *
 * The parser reads a stream of tokens and constructs a syntax tree
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
     * Parse the source code until the end of file is reached. The resulting
     * program is represented by an Abstract Syntax Tree
     *
     * @return the root of the AST created
     */
    std::unique_ptr<ASTNode> parse();

	/**
	 * Return whether errors occurred during parsing
	 * @return true if errors occurred
	 */
	bool hadErrors() const;

private:
	/**
	 * Enumeration of the error modes
	 * FATAL - throw the error and cancel parsing
	 * PANIC - throw the error and move until the next safe delimiter
	 * NON_PANIC - simply warn about the error and continue with the next token
	 * REPAIR - simply warn about the error and try to repair it
	 */
	enum class ErrorMode { FATAL, PANIC, NON_PANIC, REPAIR };

    /**
     * Read the next token in the source code
     * @return the next token
     */
	Token* move();

	/**
	 * Getter for the last token read in the source code
	 * @return the last token
	 */
	Token* previous();

	/**
	 * Getter for the next token to be read in the source code
	 * @return the next token
	 */
	Token* peek();

	/**
	 * Raise an error on the next token to be read
	 *
	 * @param error the error message
	 * @param mode the error mode
	 */
	void error(const std::string &error, ErrorMode mode = ErrorMode::PANIC);

	/**
	 * Raise an error on a specific token.
	 * When error mode is FATAL or PANIC, throw the error, otherwise the error is
	 * only reported
	 *
	 * @param error the error message
	 * @param token the token that raised the error
	 * @param mode the error mode
	 */
	void error(const std::string &error, Token* token, ErrorMode mode = ErrorMode::PANIC);

	/**
	 * Report an error to inform the user
	 * @param error the error
	 */
	static void report(const ParseError &error);

	/**
	 * Return whether the end of file has been reached
	 * @return true if the end of file has been reached
	 */
	bool isAtEnd();

	/**
     * Check if the type of the current token is the same as the type expected
     *
     * @param tokenType the type expected
     * @return true if the types are the same
     */
	bool check(TokenType tokenType);

	/**
	 * Check the type of the current token, and if it is the same as the type
	 * expected, read the next token
	 *
	 * @param tokenType the type expected
	 *
	 * @throws std::runtime_error when the expected token type is different
	 * from the current token type
	 */
	bool match(TokenType tokenType);

	/**
	 * Read the next token in file if it matches the expected token type, or
	 * throw an error if the types mismatch
	 *
	 * @param type the token type expected
	 * @param mode the error mode
	 */
	void consume(TokenType type, ErrorMode mode = ErrorMode::PANIC);

	/**
	 * Read the next token in file if it matches the expected token type, or
	 * throw an error with the given error message if the types mismatch
	 *
	 * @param type the token type expected
	 * @param mode the error mode
	 */
	void consume(TokenType type, const std::string &errorMessage, ErrorMode mode = ErrorMode::PANIC);

	/**
	 * Synchronize the parser when an error occurred and move until a delimiter
	 * token - a semicolon or a keyword
	 */
	void synchronize();

	/**
	 * Build a node representing the program
	 *
	 * @return the node created
	 */
	std::unique_ptr<StmtNode> program();

	/**
     * Build a node representing a block of statements
     *
     * @return the node created
     */
	std::unique_ptr<StmtNode> block();

	/**
	 * Build a node representing a statement
	 *
	 * @return the node created
	 */
	std::unique_ptr<StmtNode> stmt();

	/**
	 * Build a node representing an include statement
	 *
	 * @return the node created
	 */
	std::unique_ptr<StmtNode> includeStmt();

	/**
     * Build a node representing a variable declaration statement
     *
     * @return the node created
     */
	std::unique_ptr<StmtNode> declaration();

	/**
     * Build a node representing a variable assignment statement
     *
     * @return the node created
     */
	std::unique_ptr<StmtNode> varAssignStmt();

	/**
	 * Build a node representing an if/else statement
	 *
	 * @return the node created
	 */
	std::unique_ptr<StmtNode> conditionalStmt();

	/**
	 * Build a node representing a print statement
	 *
	 * @return the node created
	 */
	std::unique_ptr<StmtNode> printStmt();

	/**
	 * Build a node representing an expression statement
	 *
	 * @return the node created
	 */
	std::unique_ptr<StmtNode> expressionStmt();

	/**
     * Build a node representing an expression
     *
     * @return the node created
     */
	std::unique_ptr<ExprNode> expr();

    /**
     * Build a node representing a logical OR expression
     *
     * @return the node created
     */
	std::unique_ptr<ExprNode> logic();

    /**
     * Build a node representing a logical AND expression
     *
     * @return the node created
     */
	std::unique_ptr<ExprNode> join();

    /**
     * Build a node representing an equality or inequality expression
     *
     * @return the node created
     */
	std::unique_ptr<ExprNode> rel();

    /**
     * Build a node representing a binary operation
     *
     * @return the node created
     */
	std::unique_ptr<ExprNode> binop();

    /**
     * Build a node representing a term
     *
     * @return the node created
     */
	std::unique_ptr<ExprNode> term();

	/**
     * Build a node representing an unary
     *
     * @return the node created
     */
	std::unique_ptr<ExprNode> unary();

    /**
     * Build a node representing a factor
     *
     * @return the node created
     */
	std::unique_ptr<ExprNode> factor();

    Lexer &_lex; // The lexical analyzer
	std::unique_ptr<Token> _previous; // The last token consumed
	std::unique_ptr<Token> _lookahead; // The lookahead token
	bool _errors; // Becomes true when an error occurs
};

#endif

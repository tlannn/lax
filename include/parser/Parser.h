#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "ast/ASTFwdDecl.h"
#include "tokens/Token.h"
#include "tokens/TokenType.h"

// Forward declarations
class AST;
class Lexer;
class ParseError;
class ObjString;

/**
 * @class Parser
 * @brief A parser for parsing source code into an Abstract Syntax Tree (AST).
 *
 * The Parser class is responsible for parsing the source code into an Abstract
 * Syntax Tree (AST). It uses a lexical analyzer to read the source code and
 * extract tokens, which are then used to build the AST.
 *
 * The Parser class uses a recursive descent parsing algorithm to build the AST.
 * It uses a set of rules to parse the source code and build the AST. These
 * rules are defined in the grammar of the language.
 *
 * The Parser class also supports error handling. When an error occurs, the
 * parser tries to recover from the error and continue parsing the source code.
 * If the error cannot be recovered, the parser stops parsing and returns the
 * AST built so far.
 *
 * @note For further information about the grammar of the language and the way
 *       the code is parsed, see the documentation of the language.
 */
class Parser {
public:
    /**
     * @brief Class constructor.
     *
     * Constructs a parser for a given lexical analyzer.
     *
     * @param lex The lexical analyzer to use for tokenizing the source code.
     */
    explicit Parser(Lexer& lex);

    /**
     * @brief Parses the source code and return the AST built.
     *
     * This function is used to parse the source code until the end of file is
     * reached. The resulting program is represented by an AST.
     *
     * @throws std::runtime_error When an error occurs during parsing.
     * @return The AST built.
     */
    std::unique_ptr<AST> parse();

    /**
     * @brief Checks if there were any errors during parsing.
     * @return `true` if there were errors, `false` otherwise.
     */
    bool hadErrors() const;

private:
    /**
     * @brief Enum to represent the error mode.
     *
     * This enum is used to represent the error mode. It can be used to
     * determine how the parser should handle errors.
     */
    enum class ErrorMode {
        FATAL,      // throw the error and stop parsing
        PANIC,      // throw the error and move until the next safe delimiter
        NON_PANIC,  // report the error and move until the next safe delimiter
        REPAIR      // try to repair the error and continue parsing
    };

    /**
     * @brief Reads the next token in the source code.
     *
     * This function performs the following steps:
     * 1. Store the current token as the previous token ;
     * 2. Read the next token in the source code and store it as the lookahead
     * token.
     *
     * @return The next token in the source code.
     */
    Token* move();

    /**
     * @brief Retrieves the previous token in the source code.
     *
     * This function returns the previous token in the source code. The previous
     * token is the token that was read before the current token.
     *
     * @return The previous token in the source code.
     */
    Token* previous();

    /**
     * @brief Retrieves the lookahead token in the source code.
     * @return The lookahead token in the source code.
     */
    Token* peek();

    /**
     * @brief Raises an error on the next token to be read.
     * @param error The error message.
     * @param mode The error mode.
     */
    void error(const std::string& error, ErrorMode mode = ErrorMode::PANIC);

    /**
     * @brief Raises an error on a specific token.
     *
     * When error mode is FATAL or PANIC, throw the error, otherwise the error
     * is reported and the parser tries to recover from the error.
     *
     * @param error The error message.
     * @param token The token that raised the error.
     * @param mode The error mode.
     */
    void error(const std::string& error, Token* token,
        ErrorMode mode = ErrorMode::PANIC);

    /**
     * @brief Logs the given error.
     * @param error The error to log.
     */
    static void report(const ParseError& error);

    /**
     * @brief Checks whether the end of the file is reached.
     * @return `true` if the end of the file has been reached, `false` otherwise.
     */
    bool isAtEnd();

    /**
     * @brief Checks the given token type against the next token.
     *
     * This function takes a token type as a parameter and performs a check on
     * the type of the lookahead token.
     *
     * @param tokenType The token type to check against the lookahead token.
     * @return `true` if the type of the current token matches the desired type,
     * `false` otherwise.
     *
     * @note This function does not consume the current token.
     * @note If the end of file is reached, this function returns `false`.
     */
    bool check(TokenType tokenType);

    /**
     * @brief Checks that the next token is of the given type.
     *
     * This functions checks that the lookahead token matches the given type,
     * and consumes it in that case.
     *
     * @param tokenType The type of token expected.
     * @return `true` if the type of the next token matches the desired type,
     * `false` otherwise.
     *
     * @see check(TokenType)
     */
    bool match(TokenType tokenType);

    /**
     * @brief Consumes the next token if it matches the given type.
     *
     * This function checks if the next token matches the expected token type.
     * If so, it consumes the token, otherwise it throws an error.
     *
     * @param type The token type expected.
     * @param mode The error mode.
     *
     * @throws std::runtime_error When the expected token type is different
     * from the next token type.
     */
    void consume(TokenType type, ErrorMode mode = ErrorMode::PANIC);

    /**
     * @brief Consumes the next token if it matches the given type.
     *
     * This function checks if the next token matches the expected token type.
     * If so, it consumes the token, otherwise it throws an error with the given
     * error message.
     *
     * @param type The token type expected.
     * @param errorMessage The error message to display.
     * @param mode The error mode.
     */
    void consume(TokenType type, const std::string& errorMessage,
        ErrorMode mode = ErrorMode::PANIC);

    /**
     * @brief Synchronizes the parser when an error occurred.
     *
     * This function is used to synchronize the parser when an error occurred.
     * It moves the parser until a delimiter token is found, such as a semicolon
     * or a keyword.
     */
    void synchronize();

    /**
     * @brief Builds a string object from the given identifier.
     *
     * This function builds a string object from the given identifier. An
     * identifier is a sequence of characters that can be used to name a
     * variable, a function, a class, etc.
     *
     * Using string objects instead of identifiers allows us to store the
     * identifier in the heap, and to use it as a key in a hash table.
     *
     * @return The string object representing the identifier.
     */
    ObjString* identifier(const std::string& name);

    /**
     * @brief Builds a node representing a program.
     *
     * This function builds a node representing a program. A program is a
     * sequence of statements. It is the root node of the AST.
     *
     * @return The node representing the program.
     *
     * @see SeqNode
     * @see AST
     */
    UStmtNode program();

    /**
     * @brief Builds a node representing a block of statements.
     *
     * This function builds a node representing a block of statements. A block
     * of statements is a sequence of statements enclosed in curly braces.
     *
     * @return The node representing the block of statements.
     *
     * @see BlockNode
     */
    UBlockNode block();

    /**
     * @brief Builds a node representing a scoped block of statements.
     *
     * This function builds a node representing a scoped block of statements. A
     * scoped block of statements is a sequence of statements enclosed in curly
     * braces, and is used to create a new scope.
     *
     * @return The node representing the scoped block of statements.
     *
     * @see BlockNode
     */
    UBlockNode scopedBlock();

    /**
     * @brief Builds a node representing a statement.
     *
     * This function builds a node representing a statement. A statement is a
     * single instruction in the source code.
     *
     * @return The node representing the statement.
     *
     * @see StmtNode
     */
    UStmtNode stmt();

    /**
     * @brief Builds a node representing an include statement.
     *
     * This function builds a node representing an include statement. An include
     * statement is used to include another file in the source code.
     *
     * An include statement represents a dependency between two files. When a
     * file is included, the content of the included file is copied into the
     * current file.
     *
     * As a result, the included file is parsed as a subprogram of the current
     * file. This means that the included file can contain include statements
     * and the process will be repeated.
     *
     * @return The node representing the include statement.
     */
    UStmtNode includeStmt();

    /**
     * @brief Builds a node representing a variable declaration statement.
     *
     * This function builds a node representing a variable declaration
     * statement. A variable declaration statement is used to declare a new
     * variable, and optionally assign a value to it.
     *
     * @return The node representing the variable declaration statement.
     *
     * @see DeclNode
     */
    UDeclNode declaration();

    /**
     * @brief Builds a node representing a function declaration statement.
     *
     * This function builds a node representing a function declaration
     * statement. A function declaration statement is used to declare a new
     * function.
     *
     * @return The node representing the function declaration statement.
     *
     * @see FunNode
     */
    UFunNode function();

    /**
     * @brief Builds a node representing a return statement.
     *
     * This function builds a node representing a return statement. A return
     * statement is used to return a value from a function.
     *
     * @return The node representing the return statement.
     *
     * @see ReturnNode
     */
    UReturnNode returnStmt();

    /**
     * @brief Builds a node representing a conditional statement.
     *
     * This function builds a node representing a conditional statement. A
     * conditional statement is used to execute a block of statements if a
     * condition is true. It can also be used to execute a block of statements
     * if a condition is false.
     *
     * @return The node representing the conditional statement.
     *
     * @see ConditionalNode
     */
    UConditionalNode conditionalStmt();

    /**
     * @brief Builds a node representing a while loop statement.
     *
     * This function builds a node representing an expression statement. An
     * expression statement is used to execute an expression. It can be used to
     * call a function, to assign a value to a variable, or to perform a
     * calculation.
     *
     * @return The node representing the expression statement.
     *
     * @see StmtExpressionNode
     */
    UStmtExpressionNode expressionStmt();

    /**
     * @brief Builds a node representing an expression.
     *
     * This function builds a node representing an expression. An expression is
     * a combination of values, variables, operators, and function calls that
     * can be evaluated to a single value.
     *
     * @return The node representing the expression.
     *
     * @see ExprNode
     */
    UExprNode expr();

    /**
     * @brief Builds a node representing a variable assignment expression.
     *
     * This function builds a node representing a variable assignment expression.
     * A variable assignment expression is used to assign a value to a variable.
     *
     * When a variable is assigned a value, the value is evaluated first. If the
     * value is an expression, it is evaluated and the result is assigned to the
     * variable. If the value is a function call, the function is called and the
     * result is assigned to the variable.
     *
     * The assigned variable can then be used in an expression.
     *
     * @return The node representing the variable assignment expression.
     *
     * @see AssignNode
     */
    UExprNode assignment();

    /**
     * @brief Builds a node representing a logical OR expression.
     *
     * This function builds a node representing a logical OR expression, which
     * is a binary operation that can be used to combine two expressions using
     * the OR operator.
     *
     * The left operand is first parsed as a logical AND expression. Then, the
     * operator of the operation is checked. If the operator is a logical OR
     * operator, the right operand is parsed as a logical AND expression, and
     * the two operands are combined in a LogicalNode, with the operator
     * defining the type of the binary operation.
     *
     * If the operator is not a logical OR operator, the left operand is
     * returned as is.
     *
     * In case the right operand is followed by another logical OR expression,
     * the current LogicalNode is used as the left operand of the next binary
     * operation. This allows us to build a tree of binary operations that can
     * be evaluated recursively, so that logical OR expressions can be part of
     * other logical OR expressions.
     *
     * @note Logical OR expressions have a lower precedence than logical AND
     *       expressions.
     *
     * @return The node representing the logical OR expression.
     *
     * @see LogicalNode
     * @see join
     */
    UExprNode logic();

    /**
     * @brief Builds a node representing a logical AND expression.
     *
     * This function builds a node representing a logical AND expression, which
     * is a binary operation that can be used to combine two expressions using
     * the AND operator.
     *
     * The left operand is first parsed as a relational expression. Then, the
     * operator of the operation is checked. If the operator is a logical AND
     * operator, the right operand is parsed as a relational expression, and the
     * two operands are combined in a LogicalNode, with the operator defining
     * the type of the binary operation.
     *
     * If the operator is not a logical AND operator, the left operand is
     * returned as is.
     *
     * In case the right operand is followed by another logical AND expression,
     * the current LogicalNode is used as the left operand of the next binary
     * operation. This allows us to build a tree of binary operations that can
     * be evaluated recursively, so that logical AND expressions can be part of
     * other logical AND expressions.
     *
     * @note Logical AND expressions have a higher precedence than logical OR
     * expressions.
     *
     * @return The node representing the logical AND expression.
     *
     * @see LogicalNode
     * @see rel
     */
    UExprNode join();

    /**
     * @brief Builds a node representing a relational expression.
     *
     * This function builds a node representing a relational expression,
     * which is a binary operation that can be used to compare two expressions
     * using relational operators.
     *
     * The left operand is first parsed as an arithmetic binary operation. Then,
     * the operator of the operation is checked. If the operator is a comparison
     * operator (which checks if an operand is less than, greater than, or equal
     * to another operand), the right operand is parsed as an arithmetic binary
     * operation, and the two operands are combined in a RelationalNode, with
     * the operator defining the type of the binary operation.
     *
     * If the operator is not a comparison operator, the left operand is returned
     * as is.
     *
     * In case the right operand is followed by another relational expression,
     * the current RelationalNode is used as the left operand of the next binary
     * operation. This allows us to build a tree of binary operations that can
     * be evaluated recursively, so that relational expressions can be part of
     * other relational expressions.
     *
     * @return The node representing the relational expression.
     *
     * @see RelationalNode
     * @see arithmeticBinOp
     */
    UExprNode rel();

    /**
     * @brief Builds a node representing an arithmetic binary operation.
     *
     * This function builds a node representing an arithmetic binary operation,
     * which is a binary operation that can be used to combine two expressions
     * using basic mathematical operators : addition, subtraction,
     * multiplication, and division.
     *
     * The left term is first parsed as a multiplicative binary operation. Then,
     * the operator of the operation is checked. If the operator is an addition
     * or subtraction operator, the right term is parsed as a multiplicative
     * binary operation, and the two terms are combined in a BinOpNode, with the
     * operator defining the type of the binary operation.
     *
     * If the operator is not an addition or subtraction operator, the left term
     * is returned as is.
     *
     * In case the right term is followed by another arithmetic binary operation,
     * the current BinOpNode is used as the left operand of the next binary
     * operation. This allows us to build a tree of binary operations that can
     * be evaluated recursively, so that arithmetic binary operations can be
     * part of other arithmetic binary operations.
     *
     * As a result, this parsing method allows us to parse arithmetic binary
     * operations with the correct precedence. Multiplicative binary operations
     * have a higher precedence than arithmetic binary operations, so they are
     * evaluated first in a recursive descent parser.
     *
     * @return The node representing the binary operation.
     *
     * @see BinOpNode
     * @see multiplicativeBinOp
     */
    UExprNode arithmeticBinOp();

    /**
     * @brief Builds a node representing a multiplicative binary operation.
     *
     * This function builds a node representing a multiplicative binary
     * operation, which is a binary operation that can be used to combine two
     * expressions using multiplication or division.
     *
     * The left factor is first parsed as an unary expression. Then, the
     * operator of the operation is checked. If the operator is a multiplication
     * or division operator, the right factor is parsed as an unary expression,
     * and the two factors are combined in a BinOpNode, with the operator
     * defining the type of the binary operation.
     *
     * If the operator is not a multiplication or division operator, the left
     * factor is returned as is.
     *
     * In case the right factor is followed by another multiplicative binary
     * operator, the current BinOpNode is used as the left operand of the next
     * binary operation. This allows us to build a tree of binary operations
     * that can be evaluated recursively, so that multiplicative binary
     * operations can be part of other multiplicative binary operations.
     *
     * @return The node representing the multiplicative binary operation.
     *
     * @see BinOpNode
     * @see unary
     */
    UExprNode multiplicativeBinOp();

    /**
     * @brief Builds a node representing an unary expression.
     *
     * This function builds a node representing an unary expression. An unary
     * expression is used to apply an unary operator to an expression, like
     * negation or logical negation.
     *
     * The expression is built recursively, so that an unary expression can be
     * part of another unary expression.
     *
     * If the expression is not an unary expression, the function returns the
     * expression as is. The expression is parsed as a call expression.
     *
     * @return The node representing the unary expression.
     *
     * @see call
     */
    UExprNode unary();

    /**
     * @brief Builds a node representing a call expression.
     *
     * This function tries to build a node representing a call expression, which
     * is used to call a function.
     *
     * A call expression is composed of a callee, which is the function to be
     * called, and a list of arguments, which are the values to be passed to the
     * function. To determine the callee, the parser tries to parse a primary
     * expression that can be used as a callee.
     *
     * @return The node representing the call expression, or the callee if the
     * expression is not a valid call expression.
     *
     * @see arguments
     * @see primary
     */
    UExprNode call();

    /**
     * @brief Parses a list of call arguments and returns a call node.
     *
     * This function finishes parsing a call expression by parsing a list of
     * call arguments and returning a call node.
     *
     * @param callee The node representing the callee.
     * @return The node representing the call expression.
     */
    UExprNode arguments(UExprNode callee);

    /**
     * @brief Builds a node representing a primary expression.
     *
     * This function builds a node representing a primary expression.
     *
     * A primary expression is a single literal value, variable, or
     * parenthesized expression. A literal value is a constant primary
     * expression, like a number, a string, a boolean, or a null value.
     *
     * Identifiers are also primary expressions, but they are not considered
     * literal expressions.
     *
     * Parenthesized expressions are used to group expressions and change their
     * precedence.
     *
     * @note The null value is not yet implemented.
     *
     * @return The node representing the literal expression.
     */
    UExprNode primary();

    Lexer& m_lex;                       // The lexical analyzer
    std::unique_ptr<Token> m_previous;  // The last token consumed
    std::unique_ptr<Token> m_lookahead; // The lookahead token
    bool m_errors;                      // Becomes true when an error occurs
};

#endif

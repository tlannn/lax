#ifndef LAX_LEXER_H
#define LAX_LEXER_H

#include <string>
#include <unordered_map>

#include "tokens/token.h"
#include "tokens/num.h"
#include "tokens/op.h"
#include "tokens/word.h"
#include "tokens/type.h"

/**
 * Lexical analyzer for the Lax language
 */
class Lexer {
public:
    static int line; // Counter for the number of lines analyzed in the source code
    static int col; // Counter for the index of the character in the current line

    /**
     * Class constructor
     *
     * @param source the source code to analyze
     */
    explicit Lexer(std::string &source);

    /**
     * Continue the reading of the source code and return the next token analyzed
     *
     * @return the token analyzed
     */
    Token* nextToken();

private:
    /**
     * Reserve a word, meaning it cannot be used as an identifier (for variables,
     * functions, classes, etc.)
     *
     * @param word the word to reserve
     */
    void reserve(Word *word);

    /**
     * Read a character in the source code and update the current token
     */
    void readChar();

    /**
     * Read a character in the source code and check if it is the expected one
     *
     * @param expected the expected character
     * @return true if the character read was expected
     */
    bool readChar(char expected);

    /**
     * Check if the character is a letter
     *
     * @param c the character to check
     * @return true if the character is a letter
     */
    static bool isLetter(const char *c);

    /**
     * Check if the character is a digit
     *
     * @param c the character to check
     * @return true if the character is a digit
     */
    static bool isDigit(const char *c);

    /**
     * Check if the character is an operator. Operators are +, -, *, /
     *
     * @param c the character to check
     * @return true if the character is an operator
     */
    static bool isOperator(const char *c);

    /**
     * Check if the character is an opening or closing parenthesis
     *
     * @param c the character to check
     * @return true if the character is a parenthesis
     */
    static bool isParenthesis(const char *c);

	/**
     * Check if the character is an opening or closing brace
     *
     * @param c the character to check
     * @return true if the character is a brace
     */
    static bool isBraces(const char *c);

    /**
     * Check if the character is a colon
     *
     * @param c the character to check
     * @return true if the character is a colon
     */
    static bool isColon(const char *c);

    /**
     * Check if the character is a semicolon
     *
     * @param c the character to check
     * @return true if the character is a semicolon
     */
    static bool isSemicolon(const char *c);

    std::string _source; // The source code
    char _look; // Acts as a lookahead, useful for tokens represented by multiple characters
    int _index; // The index of the last character read
    std::unordered_map<std::string, Word*> _words; // Reserved words
};

#endif // LAX_LEXER_H

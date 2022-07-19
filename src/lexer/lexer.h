#ifndef LAX_LEXER_H
#define LAX_LEXER_H

#include <fstream>
#include <stack>
#include <string>
#include <unordered_map>

#include "lexerror.h"
#include "tokens/token.h"
#include "tokens/num.h"
#include "tokens/type.h"
#include "memento.h"

/**
 * Lexical analyzer for the Lax language
 */
class Lexer {
public:
    static std::string currentFile; // The name of the current file being read

    /**
     * Class constructor
     *
     * @param filename the source code to analyze
     */
    explicit Lexer(const std::string &filename);

	/**
	 * Open a stream to read a file and place the cursor at the beginning
	 *
	 * @param filename the name of the file to open
	 */
	void openFile(const std::string &filename);

	/**
	 * Open a file and push it on top of the stack of files opened
	 *
	 * @param filename the name of the file to open
	 */
	void pushFile(const std::string &filename);

	/**
	 * Pop the last file opened and restore the state of the previous file
	 */
	void popFile();

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
    void reserve(const std::string &word, TokenType type = TokenType::ID);

	/**
	 * Create a token of a specific type. The lexeme is deduced from the token
	 * type
	 *
	 * @param type the type of the token
	 * @return the token created
	 */
	Token* createToken(TokenType type);

	/**
	 * Create a token of specific type and lexeme
	 *
	 * @param type the type of the token
	 * @param lexeme the lexeme represented by the token
	 * @return the token created
	 */
	Token* createToken(TokenType type, const std::string &lexeme) const;

	/**
	 * Throw an error
	 *
	 * @param message the message of the error
	 */
	void error(const std::string &message) const;

	/**
	 * Return whether the cursor is at the end of the current file
	 *
	 * @return true if the end of the current file has been reached
	 */
	bool isAtEnd();

    /**
     * Read a character in the source code and return it
     *
     * @return the ascii code of the character read, or EOF if the end of file
	 * is reached
     */
    int advance();

    /**
     * Check if the next character in the source code is the expected one, and
     * if it is the case, consume it
     *
     * @param expected the expected character
     * @return true if the character read was expected
     */
    bool match(char expected);

	/**
	 * Look at the next character in the source code, but does not move the
	 * cursor
	 *
	 * @return the ascii code of the next character, or EOF if the end of file
	 * is reached
	 */
	int peek();

	/**
	 * Read a string in the source code
	 *
	 * @return the token representing the string
	 */
	Token* string();

	/**
	 * Read a number in the source code
	 *
	 * @param d the first digit of the number
	 * @return the token representing the number
	 */
	Token* number(int d);

	/**
	 * Read an identifier in the source code
	 *
	 * @param d the first letter of the identifier
	 * @return the token representing the identifier
	 */
	Token* identifier(int c);

	/**
	 * Skip an inline comment
	 */
	void inlineComment();

	/**
	 * Skip a block comment, with nested block comments
	 */
	void blockComment();

    /**
     * Check if the character is a letter or an underscore
     *
     * @param c the character to check
     * @return true if the character is a letter or an underscore
     */
    static bool isAlpha(int c);

	/**
     * Check if the character is a letter, an underscore or a digit
     *
     * @param c the character to check
     * @return true if the character is a letter, an underscore or a digit
     */
	static bool isAlphaNum(int c);

    /**
     * Check if the character is a digit
     *
     * @param c the character to check
     * @return true if the character is a digit
     */
    static bool isDigit(int c);

	/*
	 * Class attributes
	 */

	Memento *_memento;
	std::ifstream *_source;

	int _startIndex; // Index in file of the first character of the current lexeme
	int _startLine; // Line of the first character of the current lexeme
	int _startCol; // Column of the first character of the current lexeme

	int _index; // Index of the current cursor in file
	int _line; // Line of the current cursor in file
	int _col; // Column of the current cursor in file

    std::unordered_map<std::string, TokenType> _words; // Reserved words
};

#endif // LAX_LEXER_H

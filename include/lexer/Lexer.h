#ifndef LAX_LEXER_H
#define LAX_LEXER_H

#include <fstream>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>

#include "lexer/Memento.h"
#include "tokens/TokenType.h"

// Forward declarations
class Token;

/**
 * @class Lexer
 * @brief A lexical analyzer for a source code file.
 *
 * The Lexer class is responsible for analyzing a source code file and
 * extracting tokens for further processing. It provides methods for reading
 * characters from the file, matching expected characters, and creating
 * tokens based on the scanned lexemes.
 *
 * The class also supports nested files, where multiple files can be pushed
 * onto a stack and popped out when finished. This allows for handling
 * include statements and nested source code files.
 *
 * The Lexer class uses an internal stack to keep track of the current file
 * being processed and its state is saved as a Memento object. This allows
 * for restoring the state of the previous file when the current file is
 * finished being processed.
 *
 * The Lexer class uses a set of reserved words to identify keywords in
 * the source code. These reserved words cannot be used as identifiers.
 *
 * @see Memento
 */
class Lexer {
public:
    static std::string currentFile; // The name of the current file being read

    /**
     * @brief Class constructor.
     * @param filename The file containing the source code to analyze.
     */
    explicit Lexer(const std::string& filename);

    /**
     * @brief Returns the directory name of a filepath.
     *
     * This function trims the basename from a filepath, resulting in the
     * directory name.
     *
     * The filepath doesn't need to be an absolute path.
     *
     * The function returns an empty string if the filepath doesn't contain
     * any directory.
     *
     * Example:
     *
     *    getPath("path/to/file.txt") -> "path/to/"
     *    getPath("file.txt") -> ""
     *    getPath("../file.txt") -> "../"
     *
     * @note This function assumes that the filepath is a valid path.
     *
     * @param filepath The path to a file.
     * @return The directory name of the file.
     */
    static std::string getPath(const std::string& filepath);

    /**
     * @brief Opens a file to analyze.
     *
     * This function opens a file to analyze and places the cursor at the
     * beginning of the file.
     *
     * @param filename The name of the file to open.
     */
    void openFile(const std::string& filename);

    /**
     * @brief Pushes a file to analyze on top of the stack of files opened.
     *
     * This function creates a memento of the file currently being analyzed,
     * then opens the next file to analyze.
     *
     * @param filename The name of the file to open.
     */
    void pushFile(const std::string& filename);

    /**
     * @brief Pops the last file opened and restores the state of the previous
     * file.
     */
    void popFile();

    /**
     * @brief Returns the next token in the source code.
     *
     * This function analyzes the source code starting at the current cursor
     * and returns the next token encountered.
     *
     * @return The token analyzed.
     */
    std::unique_ptr<Token> nextToken();

private:
    /**
     * @brief Reserves a word.
     *
     * A reserved word cannot be used as an identifier (for variables,
     * functions, classes, etc.).
     *
     * @param word The word to reserve.
     * @param type The type of token associated with the word being reserved.
     */
    void reserve(const std::string& word, TokenType type = TokenType::ID);

    /**
     * @brief Creates a token.
     *
     * Create a token of specific type, and associate the token to a lexeme
     * based on the given type.
     *
     * @param type The type of the token to create.
     * @return The token created.
     */
    std::unique_ptr<Token> createToken(TokenType type);

    /**
     * @brief Creates a token.
     *
     * Create a token of specific type, and associate the token to the given
     * lexeme.
     *
     * @param type The type of the token.
     * @param lexeme The lexeme associated with the token.
     * @return The token created.
     */
    std::unique_ptr<Token> createToken(TokenType type,
        const std::string& lexeme) const;

    /**
     * @brief Throws a lexical error.
     *
     * This function throws a lexical error with the given message and the
     * current line and column in the file.
     *
     * @param message The message to display.
     */
    void error(const std::string& message) const;

    /**
     * @brief Checks if the end of the file is reached.
     * @return `true` if the end of the file has been reached, `false` otherwise.
     */
    bool isAtEnd();

    /**
     * @brief Reads the next character in the file.
     *
     * Read and return the next character in the file being analyzed. The
     * character returned is also consumed, thus marked as read.
     *
     * @return The ASCII value of the character read, or EOF if the end of file
	 * is reached.
     */
    int advance();

    /**
     * @brief Checks if the next character in the file was expected.
     *
     * Check if the next character in the source code is the expected one.
     * If the next character matches the character expected, it is consumed,
     * thus marked as read.
     *
     * @param expected The expected character.
     * @return `true` if the character read was expected, `false` otherwise.
     */
    bool match(char expected);

    /**
     * @brief Peeks at the next character in the file.
     *
     * Look at the next character in the current file, but does not move the
     * cursor in the file.
     *
     * @return The ASCII value of the next character, or EOF if the end of file
     * is reached.
     */
    int peek();

    /**
     * @brief Reads a string in the file and returns it as a token.
     * @return The token representing the string.
     */
    std::unique_ptr<Token> string();

    /**
     * @brief Reads a number in the file and returns it as a token.
     * @param d The first digit of the number read.
     * @return The token representing the number.
     */
    std::unique_ptr<Token> number(int d);

    /**
     * @brief Reads an identifier in the file and returns it as a token.
     * @param d The first letter of the identifier read.
     * @return The token representing the identifier.
     */
    std::unique_ptr<Token> identifier(int c);

    /**
     * @brief Skips an inline comment in code.
     *
     * This function is used to skip characters in the current file until the
     * end of the line or the end of the file.
     */
    void inlineComment();

    /**
     * @brief Skips a block comment in code.
     *
     * This function is used to skip a block comment in the file analyzed by
     * moving the cursor in the file.
     * Nested block comments are also processed in this function.
     */
    void blockComment();

    /**
     * @brief Checks whether the given character is an alphabetic character.
     *
     * This function takes an ASCII numeral representation of a character and
     * checks whether it is an alphabetic character. Both uppercase and lowercase
     * alphabetic characters are considered valid, as well as the underscore
     * character.
     *
     * @param c The ASCII value of the character to be checked.
     * @return `true` if `c` is an alphabetic character, `false` otherwise.
     */
    static bool isAlpha(int c);

    /**
     * @brief Checks if the given character is alphanumeric.
     *
     * This function checks whether the ASCII value of the given character falls
     * within the range of alphanumeric characters. In short, it checks if the
     * character is either an alphabetic character or a digit.
     *
     * @param c The ASCII value of the character to be checked.
     * @return `true` if the character is alphanumeric, `false` otherwise.
     *
     * @see isAlpha
     * @see isDigit
     */
    static bool isAlphaNum(int c);

    /**
     * @brief Determines whether a given character is a digit or not.
     *
     * This function checks whether the ASCII value of thr given character is
     * in the range of '0' to '9', indicating that it is a numeral digit.
     *
     * @param c The ASCII value of the character to be checked.
     * @return `true` if the character is a digit, `false` otherwise.
     */
    static bool isDigit(int c);

    /*
     * Class attributes
     */

    std::stack<Memento> m_mementos;
    std::unique_ptr<std::ifstream> m_source;

    int m_startIndex; // Index in file of the first character of the current lexeme
    int m_startLine; // Line of the first character of the current lexeme
    int m_startCol; // Column of the first character of the current lexeme

    int m_index; // Index of the current cursor in file
    int m_line; // Line of the current cursor in file
    int m_col; // Column of the current cursor in file

    std::unordered_map<std::string, TokenType> m_words; // Reserved words
};

#endif // LAX_LEXER_H

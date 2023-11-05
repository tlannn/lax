#ifndef LAX_TOKEN_H
#define LAX_TOKEN_H

#include <iostream>
#include <memory>
#include <string>

#include "TokenType.h"

/**
 * @class Token
 * @brief Represents a lexeme in the language.
 *
 * This class represents a token, which is a basic unit for lexical analysis in
 * many programming languages. These units are a meaningful sequence of
 * characters in the language, called lexemes.
 *
 * Tokens can represent different types of elements such as keywords,
 * identifiers, literals, operators, and punctuation symbols.
 */
class Token {
public:
    /**
     * @brief Class constructor.
     *
     * Constructs a token based on a lexeme and a token type. It also stores the
     * line and column indexes of the token position in the source code.
     *
     * @param lexeme The lexeme (character sequence) of the token.
     * @param type The token type.
     * @param line The line where the token is located in the source code.
     * @param col The column where the token is located in the source code.
     */
    Token(std::string lexeme, TokenType type, int line, int col);

    /**
     * @brief Class constructor.
     *
     * Constructs a token based on a lexeme and a token type.
     *
     * @param lexeme The lexeme (character sequence) of the token.
     * @param type The token type.
     *
     * @note The line and column indexes of the token position in the source
     *       code are initialized to an invalid value.
     */
    Token(const std::string& lexeme, TokenType type);

    /**
     * @brief Class destructor.
     *
     * Default destructor.
     */
    virtual ~Token() = default;

    /**
     * @brief Returns the lexeme for the given token type.
     *
     * Some tokens have a fixed lexeme, such as keywords and operators, while
     * others have a variable lexeme, such as identifiers and literals.
     *
     * This function returns the lexeme associated with the given token type, if
     * it has a fixed lexeme, or an empty string otherwise.
     *
     * @param type The token type.
     * @return The lexeme of the token.
     */
    static std::string lexeme(TokenType type);

    /**
     * @brief Returns the type of the token.
     * @return The token type.
     */
    TokenType getType() const;

    /**
     * @brief Retrieves the line where the token is located in the source code.
     * @return The line index.
     */
    int getLine() const;

    /**
     * @brief Retrieves the column where the token is located in the source code.
     * @return The column index.
     */
    int getColumn() const;

    /**
     * @brief Stringifies the token.
     *
     * This function is virtual, which means that it can be overridden by
     * subclasses.
     *
     * It returns by default the lexeme of the token.
     *
     * @return The string representation of the token.
     */
    virtual std::string toString() const;

protected:
    TokenType m_type;
    std::string m_text;
    int m_line;
    int m_col;
};

typedef std::unique_ptr<Token> UToken;

#endif // LAX_TOKEN_H

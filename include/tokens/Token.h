#ifndef LAX_TOKEN_H
#define LAX_TOKEN_H

#include <iostream>
#include <memory>
#include <string>

#include "TokenType.h"

/**
 * A token represents a lexeme in the language, a meaningful sequence of characters.
 */
class Token {
public:
     /**
      * Class constructor
      * @param lexeme the lexeme (character sequence) of the token
      * @param type the token type
      * @param line the line where the token is located in the source code
      * @param col the column where the token is located in the source code
      */
    Token(const std::string &lexeme, TokenType type, int line, int col);

	/**
	 * Class constructor
	 * @param lexeme the lexeme (character sequence) of the token
	 * @param type the token type
	 */
	Token(const std::string &lexeme, TokenType type);

	/**
	 * Class destructor
	 */
	virtual ~Token() = default;

	/**
	 * Return the lexeme associated to a token type.
	 * The lexemes are language-defined
	 *
	 * @param type the token type
	 * @return the lexeme
	 */
	static std::string lexeme(TokenType type);

    /**
     * Getter for the token type
     *
     * @return the token type
     */
    TokenType getType() const;

	/**
	 * Getter for the token line
	 * @return the line
	 */
	int getLine() const;

	/**
	 * Getter for the token column
	 * @return the column
	 */
	int getColumn() const;

	/**
     * Stringify the token
     *
     * @return a string representing the token
     */
	virtual std::string toString() const;

protected:
    TokenType _type;
    std::string _text;
	int _line;
	int _col;
};

typedef std::unique_ptr<Token> UToken;

#endif // LAX_TOKEN_H

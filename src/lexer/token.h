#ifndef LAX_TOKEN_H
#define LAX_TOKEN_H

#include <string>

#include "tokentype.h"

/**
 * A token represents a lexeme in the language, a meaningful sequence of characters.
 */
class Token {
public:
    /// Class constructor
    Token();

    /**
     * Class constructor
     *
     * @param type the type of the token
     */
    explicit Token(TokenType type);

    /**
     * Class constructor
     *
     * @param lexeme the sequence of characters forming the lexeme
     * @param type the type of the token
     */
    Token(const std::string &lexeme, TokenType t);

    /**
     * Getter for the token type
     *
     * @return the token type
     */
    int getType() const;

    /**
     * Stringify the token
     *
     * @return a string representing the token
     */
    virtual std::string toString() const;

protected:
    TokenType _type;
    std::string _text;
};

#endif // LAX_TOKEN_H

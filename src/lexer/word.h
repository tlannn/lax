#ifndef LAX_WORD_H
#define LAX_WORD_H

#include <string>

#include "token.h"
#include "tokentype.h"

/**
 * Token for a word in the language
 *
 * Words can be keywords (reserved, language-specific), identifiers or
 * composite tokens (like multi-characters operators)
 */
class Word : public Token {
public:
    static Word TRUE; // Word meaning truthfulness
    static Word FALSE; // Word meaning falseness
    static Word AND; // Logical operator and
    static Word OR; // Logical operator or
    static Word EQ; // Equality operator
    static Word NEQ; // Not equal operator
    static Word SL; // Strictly less operator
    static Word LE; // Less or equal operator
    static Word SG; // Strictly greater operator
    static Word GE; // Greater or equal operator
    static Word IF; // Word indicating debut of conditional statement
    static Word ELSE; // Word indicating debut of statement when conditional statement is evaluated to false
    static Word PRINT; // Word 'print'

    /**
     * Class constructor
     *
     * @param s the sequence of characters forming the lexeme
     * @param t the type of the token
     */
    Word(const std::string &word, TokenType type);

    /// Stringify the token
    std::string toString() const override;
};

#endif // LAX_WORD_H

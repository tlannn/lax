#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <unordered_map>

#include "token.h"

/**
 * Lexical analyzer for the Lax language
 */
class Lexer {
    public:
        static int line; // Counter for the number of lines analyzed in the source code

        /**
         * Class constructor
         *
         * @param source the source code to analyze
         */
        Lexer(std::string source);

        /**
         * Continue the reading of the source code and return the next token analyzed
         *
         * @return the token analyzed
         */
        Token* nextToken();

    private:
        /**
         * Reserve a word, meaning it cannot be used as an identier (for variables,
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
        bool isLetter(char *c);

        /**
         * Check if the character is a digit
         *
         * @param c the character to check
         * @return true if the character is a digit
         */
        bool isDigit(char *c);

        /**
         * Check if the character is an operator. Operators are +, -, *, /
         *
         * @param c the character to check
         * @return true if the character is an operator
         */
        bool isOperator(char *c);

        /**
         * Check if the character is an opening or closed parenthesis
         *
         * @param c the character to check
         * @return true if the character is a parenthesis
         */
        bool isParenthesis(char *c);

        /**
         * Check if the character is a semicolon
         *
         * @param c the character to check
         * @return true if the character is a semicolon
         */
        bool isSemicolon(char *c);

        std::string _source; // The source code
        char _look; // Acts as a lookahead, useful for tokens represented by multiple characters
        int _index; // The index of the last character read
        std::unordered_map<std::string, Word*> _words; // Reserved words
};

#endif

#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

/// Enumeration of the token types
enum TokenType {
    NONE = 256, // No type
    ID = 257, // Identifier (for variables, functions, etc.)
    TYPE = 258, // Basic type (integer, boolean, etc.)
    TRUE = 259, // True constant
    FALSE = 260, // False constant
    NUM = 261, // Numeric value
    REAL = 262, // Real number
    OP = 263, // Operator (+, -, *, /)
    LPAREN = 264, // Left parenthesis
    RPAREN = 265, // Right parenthesis
    LBRACK = 266, // Left bracket
    RBRACK = 267, // Right bracket
    LSBRACK = 268, // Left square bracket
    RSBRACK = 269, // Right square bracket
    EQ = 270, // Equality sign
    NEQ = 271, // Not equal sign
    SL = 272, // Strictly less sign
    LE = 273, // Less or equal sign
    SG = 274, // Strictly greater sign
    GE = 275, // Greater or equal sign
    BANG = 276, // Exclamation mark, logical not operator
    AND = 277, // Logical and operator
    OR = 278, // Logical or operator
    DO = 279, // Do keyword
    BREAK = 280, // Break keyword
    IF = 281, // If keyword
    ELSE = 282, // Else keyword
    WHILE = 283, // While keyword
    FOR = 284, // For keyword
    PRINT = 285, // Print keyword
    SEMICOL = 286, // Semicolon
    END = 287 // End of file
};

/**
 * A token represents a lexeme in the language, a meaningful sequence of characters.
 */
class Token {
    public:
        /// Class contructor
        Token();

        /**
         * Class constructor
         *
         * @param t the type of the token
         */
        Token(TokenType t);

        /**
         * Class constructor
         *
         * @param s the sequence of characters forming the lexeme
         * @param t the type of the token
         */
        Token(std::string s, TokenType t);

        /**
         * Getter for the token type
         *
         * @return the token type
         */
        int getType();

        /**
         * Stringify the token
         *
         * @return a string representing the token
         */
        virtual std::string toString();

    protected:
        TokenType _type;
        std::string _text;
};

/**
 * Token for a numeric value in the language
 */
class Num : public Token {
    public:
        /**
         * Class constructor
         *
         * @param v the numeric value
         */
        Num(int v);

        /**
         * Getter for the numeric value of the token
         *
         * @return the value
         */
        int getValue();

        /// Stringify the token
        virtual std::string toString();
};


/**
 * Token for an operator in the language
 */
class Op : public Token {
    public:
        /**
         * Class constructor
         *
         * @param op the operator
         */
        Op(char op);

        /// Stringify the token
        virtual std::string toString();
};

/**
 * Token for a word in the language
 *
 * Words can be keywords (reserved, language-specific), identifiers or
 * composite tokens (like multi-characters operators)
 */
class Word : public Token {
    public:
        static Word TRUE; // Word 'true'
        static Word FALSE; // Word 'false'
        static Word AND; // Logical operator and
        static Word OR; // Logical operator or
        static Word EQ; // Equality operator
        static Word NEQ; // Not equal operator
        static Word SL; // Strictly less operator
        static Word LE; // Less or equal operator
        static Word SG; // Strictly greater operator
        static Word GE; // Greater or equal operator
        static Word IF; // Word 'if'
        static Word PRINT; // Word 'print'

        /**
         * Class constructor
         *
         * @param s the sequence of characters forming the lexeme
         * @param t the type of the token
         */
        Word(std::string s, TokenType t);

        /// Stringify the token
        virtual std::string toString();
};

class Type : public Word {
    public:
        static Type INT; // Basic type 'int' for integers
        static Type BOOL; // Basic type 'bool' for booleans

        /**
         * Class constructor
         *
         * @param s the sequence of characters forming the lexeme
         * @param t the type of the token
         * @param size the size in bytes for the type
         */
        Type(std::string s, TokenType t, int size);

        /**
         * Getter for the type size
         *
         * @return the size in bytes of the type
         */
        int getSize();

        /**
         * Overload the equality operator to compare two types
         *
         * @param t1 the first type to compare
         * @param t2 the second type to compare
         * @return true if the two types are equal
         */
        friend bool operator== (Type &t1, Type &t2);

        /**
         * Overload the not equal operator to compare two types
         *
         * @param t1 the first type to compare
         * @param t2 the second type to compare
         * @return true if the two types are not equal
         */
        friend bool operator!= (const Type &t1, const Type &t2);

    protected:
        int _size;
};

#endif

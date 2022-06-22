#ifndef LAX_TOKENTYPE_H
#define LAX_TOKENTYPE_H

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
    VAR = 279, // Var keyword
    DO = 280, // Do keyword
    BREAK = 281, // Break keyword
    IF = 282, // If keyword
    ELSE = 283, // Else keyword
    WHILE = 284, // While keyword
    FOR = 285, // For keyword
    PRINT = 286, // Print keyword
    SIMEQ = 287, // Semicolon
    SEMICOL = 288, // Semicolon
    COLON = 289, // Semicolon
    END = 290 // End of file
};

#endif // LAX_TOKENTYPE_H

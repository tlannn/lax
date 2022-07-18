#ifndef LAX_TOKENTYPE_H
#define LAX_TOKENTYPE_H

/// Enumeration of the token types
enum TokenType {
    UNKNOWN = 256, // No type
    ID = 257, // Identifier (for variables, functions, etc.)
    TYPE = 258, // Basic type (integer, boolean, etc.)
    TRUE = 259, // True constant
    FALSE = 260, // False constant
    NUM = 261, // Numeric value
    REAL = 262, // Real number
	STRING = 263, // Character sequence
	PLUS = 264, // Addition operator
	MINUS = 265, // Subtraction operator
	STAR = 266, // Multiplication operator
	SLASH = 267, // Division operation
    LPAREN = 268, // Left parenthesis
    RPAREN = 269, // Right parenthesis
    LBRACE = 270, // Left bracket
    RBRACE = 271, // Right bracket
    LBRACK = 272, // Left square bracket
    RBRACK = 273, // Right square bracket
    EQ = 274, // Equality sign
    NEQ = 275, // Not equal sign
    SL = 276, // Strictly less sign
    LE = 277, // Less or equal sign
    SG = 278, // Strictly greater sign
    GE = 279, // Greater or equal sign
    BANG = 280, // Exclamation mark, logical not operator
	SIMEQ = 281, // Assignment operator
	SEMICOL = 282, // Semicolon
	COLON = 283, // Colon
    AND = 284, // Logical and operator
    OR = 285, // Logical or operator
    VAR = 286, // Var keyword
    DO = 287, // Do keyword
    BREAK = 288, // Break keyword
    IF = 289, // If keyword
    ELSE = 290, // Else keyword
    WHILE = 291, // While keyword
    FOR = 292, // For keyword
    INCLUDE = 293, // Include keyword
    PRINT = 294, // Print keyword
    END = 295 // End of file
};

#endif // LAX_TOKENTYPE_H

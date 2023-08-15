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
	STR = 263, // Character sequence
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
	COMMA = 284, // Comma
    AND = 285, // Logical and operator
    OR = 286, // Logical or operator
    VAR = 287, // Var keyword
    FUN = 288, // Fun keyword
    RETURN = 289, // Return keyword
    DO = 290, // Do keyword
    BREAK = 291, // Break keyword
    IF = 292, // If keyword
    ELSE = 293, // Else keyword
    WHILE = 294, // While keyword
    FOR = 295, // For keyword
    INCLUDE = 296, // Include keyword
    END = 297 // End of file
};

#endif // LAX_TOKENTYPE_H

#ifndef LAX_LEXERROR_H
#define LAX_LEXERROR_H

#include <string>

#include "common/CompileTimeException.h"

/**
 * @class LexError
 * @brief Exception thrown when a lex error is encountered.
 *
 * This class represents a lex error. It is thrown when a lex error is
 * encountered during the lexing of the program.
 */
class LexError : public CompileTimeException {
public:
    /**
     * @brief Class constructor.
     *
     * Constructs a lex error given the file, line, column, message, and
     * type of the error.
     *
     * @param file The file where the error occurred.
     * @param line The line where the error occurred.
     * @param col The column where the error occurred.
     * @param message The error message.
     * @param type The type of the error.
     */
    LexError(const std::string& file, int line, int col,
        const std::string& message, const std::string& type);
};

#endif // LAX_LEXERROR_H

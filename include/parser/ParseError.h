#ifndef LAX_PARSEERROR_H
#define LAX_PARSEERROR_H

#include <string>

#include "common/CompileTimeException.h"

/**
 * @class ParseError
 * @brief Exception thrown when a parse error is encountered.
 *
 * This class represents a parse error. It is thrown when a parse error is
 * encountered during the parsing of the program.
 */
class ParseError : public CompileTimeException {
public:
    /**
     * @brief Class constructor.
     *
     * Constructs a parse error given the file, line, column, message, and
     * type of the error.
     *
     * @param file The file where the error occurred.
     * @param line The line where the error occurred.
     * @param col The column where the error occurred.
     * @param message The error message.
     * @param type The type of the error.
     */
    ParseError(const std::string& file, int line, int col,
        const std::string& message, const std::string& type);
};

#endif // LAX_PARSEERROR_H

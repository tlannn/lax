#ifndef LAX_SEMANTICERROR_H
#define LAX_SEMANTICERROR_H

#include <string>

#include "common/CompileTimeException.h"

/**
 * @class SemanticError
 * @brief Exception thrown when a semantic error is encountered.
 *
 * This class represents a semantic error. It is thrown when a semantic error is
 * encountered during the semantic analysis of the program.
 */
class SemanticError : public CompileTimeException {
public:
    /**
     * @brief Class constructor.
     *
     * Constructs a semantic error given the file, line, column, message, and
     * type of the error.
     *
     * @param file The file where the error occurred.
     * @param line The line where the error occurred.
     * @param col The column where the error occurred.
     * @param message The error message.
     * @param type The type of the error.
     */
    SemanticError(const std::string& file, int line, int col,
        const std::string& message, const std::string& type);
};

#endif // LAX_SEMANTICERROR_H

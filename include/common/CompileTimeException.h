#ifndef LAX_COMPILETIMEEXCEPTION_H
#define LAX_COMPILETIMEEXCEPTION_H

#include <string>

#include "Exception.h"

/**
 * @class CompileTimeException
 * @brief Exception thrown when a compile-time error is encountered.
 *
 * This class represents a compile-time exception. It is thrown when a
 * compile-time error is encountered during the compilation of the program.
 *
 * Compile-time exceptions are aware of the location in the source code where
 * the error occurred.
 *
 * @note This class is abstract and should not be instantiated directly.
 *       Instead, use one of its subclasses.
 */
class CompileTimeException : public Exception {
public:
    /**
     * @brief Class constructor.
     *
     * Create a compile-time exception given a file and a position and this file.
     *
     * @param file The file where the exception occurred.
     * @param line The line where the exception occurred.
     * @param col The column where the exception occurred.
     * @param message The exception message.
     * @param type The type of exception.
     */
    CompileTimeException(std::string file, int line, int col,
        std::string message, std::string type);

    /**
     * @copydoc Exception::what()
     */
    const char* what() const noexcept override;

protected:
    const int m_line;
    const int m_col;
    const std::string m_file;
};

#endif // LAX_COMPILETIMEEXCEPTION_H

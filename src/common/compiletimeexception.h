#ifndef LAX_COMPILETIMEEXCEPTION_H
#define LAX_COMPILETIMEEXCEPTION_H

#include <string>

#include "exception.h"

/**
 * Class for exceptions raised during compile time
 */
class CompileTimeException : public Exception {
public:
	/**
	 * Class constructor
	 * @param file the file where the exception occurred
	 * @param line the line where the exception occurred
	 * @param col the column where the exception occurred
	 * @param message the exception message
	 * @param type the type of exception
	 */
	CompileTimeException(std::string file, int line, int col,
						 std::string message, std::string type);

	/**
	 * Get string identifying exception
	 * @return the string
	 */
	const char* what() const noexcept override;

protected:
	const int _line;
	const int _col;
	const std::string _file;
};

#endif // LAX_COMPILETIMEEXCEPTION_H

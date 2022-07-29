#ifndef LAX_PARSEERROR_H
#define LAX_PARSEERROR_H

#include <string>

#include "common/CompileTimeException.h"

/**
 * Exception class for errors occurring during parsing
 */
class ParseError : public CompileTimeException {
public:
	/**
	 * Class constructor
	 * @param file the file where the exception occurred
	 * @param line the line where the exception occurred
	 * @param col the column where the exception occurred
	 * @param message the exception message
	 * @param type the type of exception
	 */
	ParseError(const std::string &file, int line, int col, const std::string &message, const std::string &type);
};

#endif // LAX_PARSEERROR_H

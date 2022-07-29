#ifndef LAX_LEXERROR_H
#define LAX_LEXERROR_H

#include <string>

#include "common/compiletimeexception.h"

/**
 * Exception class for errors occurring during lexical analysis
 */
class LexError : public CompileTimeException {
public:
	/**
	 * Class constructor
	 * @param file the file where the exception occurred
	 * @param line the line where the exception occurred
	 * @param col the column where the exception occurred
	 * @param message the exception message
	 * @param type the type of exception
	 */
	LexError(const std::string &file, int line, int col, const std::string &message, const std::string &type);
};

#endif // LAX_LEXERROR_H

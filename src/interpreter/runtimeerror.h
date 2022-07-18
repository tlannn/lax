#ifndef LAX_RUNTIMEERROR_H
#define LAX_RUNTIMEERROR_H

#include <string>

#include "common/exception.h"

/**
 * Exception class for errors occurring during runtime
 */
class RuntimeError : public Exception {
public:
	/**
	 * Class constructor
	 * @param file the file where the exception occurred
	 * @param line the line where the exception occurred
	 * @param col the column where the exception occurred
	 * @param message the exception message
	 * @param type the type of exception
	 */
	RuntimeError(const std::string &file, int line, int col, const std::string &message, const std::string &type);
};

#endif // LAX_RUNTIMEERROR_H

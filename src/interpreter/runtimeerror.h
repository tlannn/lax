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
	 * @param message the exception message
	 * @param type the type of exception
	 */
	explicit RuntimeError(std::string message, std::string type = "");
};

#endif // LAX_RUNTIMEERROR_H

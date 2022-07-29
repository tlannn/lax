#ifndef LAX_EXCEPTION_H
#define LAX_EXCEPTION_H

#include <exception>
#include <string>

/**
 * Base exception class
 */
class Exception : public std::exception {
public:
	/**
	 * Class constructor
	 * @param message the exception message
	 * @param type the type of exception
	 */
	explicit Exception(std::string message, std::string type = "");

	/**
	 * Get string identifying exception
	 * @return the string
	 */
	const char* what() const noexcept override;

protected:
	const std::string _message;
	const std::string _type;
};

#endif // LAX_EXCEPTION_H

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
	 * @param file the file where the exception occurred
	 * @param line the line where the exception occurred
	 * @param col the column where the exception occurred
	 * @param message the exception message
	 * @param type the type of exception
	 */
	Exception(const std::string &file, int line, int col, const std::string &message, const std::string &type);

	/**
	 * Get string identifying exception
	 * @return the string
	 */
	const char* what() const noexcept override;

protected:
	const int _line;
	const int _col;
	const std::string _file;
	const std::string _message;
	const std::string _type;
};

#endif // LAX_EXCEPTION_H

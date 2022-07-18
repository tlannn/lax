#include "exception.h"

/// Class constructor
Exception::Exception(const std::string &file, const int line, const int col, const std::string &message,
					 const std::string &type) : std::exception(),
					 _file(file), _line(line), _col(col), _message(message), _type(type) {}

/// Get string identifying exception
const char *Exception::what() const noexcept {
	return (
			new std::string(_file + ":" + std::to_string(_line) + ":" + std::to_string(_col) + ": " +
							_type + ": " + _message)
	)->c_str();
}

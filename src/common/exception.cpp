#include "exception.h"

/// Class constructor
Exception::Exception(std::string message, std::string type) :
					 std::exception(), _message(std::move(message)), _type(std::move(type)) {}

/// Get string identifying exception
const char *Exception::what() const noexcept {
	if (_type.empty())
		return _message.c_str();

	else
		return (new std::string(_type + ": " + _message))->c_str();
}

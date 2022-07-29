#include "common/CompileTimeException.h"

/// Class constructor
CompileTimeException::CompileTimeException(std::string file, const int line, const int col,
										   std::string message, std::string type) :
										   Exception(std::move(message), std::move(type)),
										   _file(std::move(file)), _line(line), _col(col) {}

/// Get string identifying exception
const char *CompileTimeException::what() const noexcept {
	return (new std::string(_file + ":" +
							std::to_string(_line) + ":" + std::to_string(_col) + ": " +
							Exception::what())
			)->c_str();
}

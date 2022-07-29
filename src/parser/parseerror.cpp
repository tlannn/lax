#include "parseerror.h"

/// Class constructor
ParseError::ParseError(const std::string &file, const int line, const int col, const std::string &message,
					   const std::string &type) : CompileTimeException(file, line, col, message, type) {}

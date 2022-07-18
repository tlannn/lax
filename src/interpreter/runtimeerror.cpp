#include "runtimeerror.h"

/// Class constructor
RuntimeError::RuntimeError(const std::string &file, const int line, const int col, const std::string &message,
							 const std::string &type) : Exception(file, line, col, message, type) {}

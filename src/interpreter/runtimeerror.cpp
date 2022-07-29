#include "runtimeerror.h"

/// Class constructor
RuntimeError::RuntimeError(std::string message, std::string type) :
						   Exception(std::move(message), std::move(type)) {}

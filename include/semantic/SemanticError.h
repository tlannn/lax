#ifndef LAX_SEMANTICERROR_H
#define LAX_SEMANTICERROR_H

#include <string>

#include "common/CompileTimeException.h"

class SemanticError : public CompileTimeException {
public:
	SemanticError(const std::string &file, int line, int col, const std::string &message, const std::string &type);
};

#endif // LAX_SEMANTICERROR_H

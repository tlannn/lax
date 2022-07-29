#ifndef LAX_LAX_H
#define LAX_LAX_H

#include <memory>
#include <string>

#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "interpreter/Interpreter.h"
#include "semantic/SemanticAnalyzer.h"
#include "utils/Logger.h"

/**
 * Entry class to handle a Lax source code
 */
class Lax {
public:
	/**
	 * Run a source file with the Lax interpreter
	 * @param filepath the path to the source file
	 */
	static void run(const std::string &filepath);

private:
	/**
	 * Read a source file
	 * @param filepath
	 * @return
	 */
	static std::string readFile(const std::string &filepath);
};

#endif // LAX_LAX_H

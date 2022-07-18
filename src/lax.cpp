#include "lax.h"

/// Run a source file with the Lax interpreter
void Lax::run(const std::string &filepath) {
	// Read the source code from the file
	const std::string source = readFile(filepath);

	try {
		// Create the lexical analyser for the file
		Lexer lexer(filepath);

		// Parse the file
		Parser parser(lexer);
		ASTNode* ast = parser.parse();

		// Stop here if there is syntax errors
		if (parser.hadErrors())
			return;

		// Start semantic analysis
		SemanticAnalyzer analyzer(ast);
		analyzer.analyze();

		// Stop here if there is semantic errors
		if (analyzer.hadErrors())
			return;

		// Interpret the program
		Interpreter interpreter(ast);
		interpreter.interpret();
	} catch (std::exception &e) {
		Logger::error(e.what());
		exit(EXIT_FAILURE);
	}
}

/// Read a source file
std::string Lax::readFile(const std::string &filepath) {
	std::string source;
	std::string line;
	std::ifstream file;
	file.open(filepath);

	if (file.is_open()) {
		while (getline(file, line))
			source += line + '\n';

		file.close();
	}

	else
		Logger::error("Unable to open file " + filepath);

	return source;
}

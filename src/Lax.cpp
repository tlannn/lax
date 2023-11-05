#include "Lax.h"
#include "ast/AST.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "utils/Logger.h"
#include "vm/VM.h"

void Lax::interpret(const std::string& filepath) {
    try {
        // Create the lexical analyser for the file
        Lexer lexer(filepath);

        // Parse the file
        Parser parser(lexer);
        std::unique_ptr<AST> ast = parser.parse();

        // Stop here if there is syntax errors
        if (parser.hadErrors())
            return;

        VM vm;
        vm.interpret(*ast);
    } catch (std::exception& e) {
        Logger::error(e.what());
        exit(EXIT_FAILURE);
    }
}

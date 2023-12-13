#include "Lax.h"
#include "ast/AST.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "semantic/Definer.h"
#include "semantic/HoistingPass.h"
#include "semantic/Resolver.h"
#include "semantic/TypeChecker.h"
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

        const bool success = pass(
            HoistingPass(*ast),
            Definer(*ast),
            Resolver(*ast),
            TypeChecker(*ast)
        );

        if (!success) {
            Logger::log("Errors encountered during the code verification");
            return;
        }

        VM vm;
        vm.interpret(*ast);
    } catch (std::exception& e) {
        Logger::error(e.what());
        exit(EXIT_FAILURE);
    }
}

template<typename T>
bool Lax::pass(T&& t) {
    t.analyze();
    return !t.hadErrors();
}

template<typename T, typename... Ts>
bool Lax::pass(T&& first, Ts&&... rest) {
    if (!pass(first))
        return false;

    return pass(rest...);
}

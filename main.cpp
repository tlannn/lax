#include <iostream>
#include <fstream>
#include <string>

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "interpreter/interpreter.h"
#include "semantic/semanticanalyzer.h"

using namespace std;

#define NO_ARGUMENT_CODE 1

/**
 * Read a file
 *
 * @param filename the name of the file to read
 * @return the file content
 */
string readFile(string filename);

/// Main
int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Please specify a file to run\n");
        exit(NO_ARGUMENT_CODE);
    }

    string filename = argv[1];
    string source = readFile(filename);

    // Output source code
    cout << source << endl;
    cout << "------------------" << endl;
    cout << " START OF PROGRAM" << endl;
    cout << "------------------" << endl;

    // Start interpreter
    Lexer lexer(source);
    Parser parser(lexer);
    SemanticAnalyzer analyzer(parser);
    analyzer.analyze();
    Interpreter interpreter(parser);
    interpreter.interpret();

    return 0;
}

/// Read a file
string readFile(string filename) {
    string source = "";
    string line;
    ifstream file;
    file.open(filename);

    if (file.is_open()) {
        while (getline(file, line))
            source += line + '\n';

        file.close();
    }

    else
        cout << "Unable to open file";

    return source;
}

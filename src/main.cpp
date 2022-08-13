#include <iostream>
#include <string>

#include "Lax.h"

#define NO_ARGUMENT_CODE 1

/// Main
int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Please specify a file to run." << std::endl;
        exit(NO_ARGUMENT_CODE);
    }

	// Interpreter mode
	else if (argc == 2) {
		std::string filepath = argv[1];
		Lax::interpret(filepath);
	}

	else {
		std::cout << "Too much arguments." << std::endl;
		exit(EXIT_FAILURE);
	}

//	// Compiler mode
//	else {
//		std::string command = argv[1];
//		std::string filepath = argv[2];
//
//		if (command == "build")
//			Lax::compile(filepath);
//
//		else if(command == "run")
//			Lax::run(filepath);
//
//		else {
//			std::cout << "Unknown command " << command << "." << std::endl;
//			exit(EXIT_FAILURE);
//		}
//	}

    return EXIT_SUCCESS;
}

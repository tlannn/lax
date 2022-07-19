#include <iostream>
#include <string>

#include "lax.h"

#define NO_ARGUMENT_CODE 1

/// Main
int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cout << "Please specify a file to run" << std::endl;
        exit(NO_ARGUMENT_CODE);
    }

    std::string filepath = argv[1];
	Lax::run(filepath);

    return 0;
}

#ifndef LAX_LAX_H
#define LAX_LAX_H

#include <iterator>
#include <memory>
#include <string>

/**
 * Entry class to handle a Lax source code
 */
class Lax {
public:
    /**
     * Interpret a source file with the Lax interpreter
     * @param filepath the path to the source file
     */
    static void interpret(const std::string& filepath);
};

#endif // LAX_LAX_H

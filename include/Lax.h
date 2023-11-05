#ifndef LAX_LAX_H
#define LAX_LAX_H

#include <iterator>
#include <memory>
#include <string>

/**
 * @class Lax
 * @brief The main class of the Lax interpreter.
 *
 * This class is the main class of the Lax interpreter. It is responsible for
 * interpreting a source file.
 */
class Lax {
public:
    /**
     * @brief Interprets a source file.
     *
     * This takes the path to the source file as a parameter and interprets it.
     *
     * @param filepath The path to the source file.
     */
    static void interpret(const std::string& filepath);
};

#endif // LAX_LAX_H

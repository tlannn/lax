#ifndef LAX_LOGGER_H
#define LAX_LOGGER_H

#include <iostream>
#include <string>

// Code for white color displays in gray, so instead no code is used to display
// in white by default
#define COLOR_WHITE "" // "\u001b[37m"
#define COLOR_RED "\u001b[31m"
#define COLOR_YELLOW "\u001b[33m"
#define COLOR_RESET "\u001b[0m"

/**
 * @class Logger
 * @brief Utility class to log messages to the standard output stream.
 *
 * This class provides static methods to log messages to the standard output
 * stream. It can be used to log messages of different types, such as regular
 * messages, warnings, and errors.
 */
class Logger {
public:
    /**
     * @brief Logs a message to the console.
     *
     * This function logs a message to the console. The message is provided as
     * a parameter and is printed to the standard output stream.
     *
     * @param message The message to display.
     */
    static void log(const std::string &message);

    /**
     * @brief Logs a warning message.
     *
     * This function displays a warning message to the console using the
     * provided message.
     *
     * @param message The warning message to display.
     */
    static void warning(const std::string &message);

    /**
     * @brief Logs an error message.
     *
     * This function displays an error message to the console using the
     * provided message.
     *
     * @param message The error message to display.
     */
    static void error(const std::string &message);

private:
    /**
     * @brief Represents the type of message to be logged.
     *
     * This enum provides the different types of messages that can be logged to
     * the console. It is used to determine the color of the message to be
     * displayed.
     */
	enum LogType {
		LOG,
		WARNING,
		ERROR
	};

    /**
     * @brief Displays a message of a given type to the console.
     *
     * This function displays a message of a given type to the console. The
     * message is provided as a parameter and is printed to the standard output
     * stream.
     *
     * The type of message is also provided as a parameter and is used
     * to determine the color of the message to be displayed.
     *
     * @param type The type of message to display.
     * @param message The message to display.
     */
    static void display(LogType type, const std::string &message);
};

#endif // LAX_LOGGER_H

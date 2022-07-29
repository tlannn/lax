#ifndef LAX_LOGGER_H
#define LAX_LOGGER_H

#define COLOR_WHITE "\u001b[37m"
#define COLOR_RED "\u001b[31m"
#define COLOR_YELLOW "\u001b[33m"
#define COLOR_RESET "\u001b[0m"

#include <iostream>
#include <string>

enum LogType {
	LOG,
	WARNING,
	ERROR
};

class Logger {
public:
	static void log(std::string message);
	static void warning(std::string message);
	static void error(std::string message);

private:
	static void display(LogType type, std::string message);
};


#endif // LAX_LOGGER_H

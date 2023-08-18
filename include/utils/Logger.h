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

class Logger {
public:
	static void log(const std::string &message);
	static void warning(const std::string &message);
	static void error(const std::string &message);

private:
	enum LogType {
		LOG,
		WARNING,
		ERROR
	};

	static void display(LogType type, const std::string &message);
};


#endif // LAX_LOGGER_H

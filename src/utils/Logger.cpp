#include "utils/Logger.h"

void Logger::log(const std::string& message) {
    Logger::display(LogType::LOG, message);
}

void Logger::warning(const std::string& message) {
    Logger::display(LogType::WARNING, message);
}

void Logger::error(const std::string& message) {
    Logger::display(LogType::ERROR, message);
}

void Logger::display(LogType type, const std::string& message) {
    std::string color;

    switch (type) {
        case LogType::WARNING:
            color = COLOR_YELLOW;
            break;
        case LogType::ERROR:
            color = COLOR_RED;
            break;
        default:
            color = COLOR_WHITE;
            break;
    }

    std::cout << color << message << COLOR_RESET << std::endl;
}

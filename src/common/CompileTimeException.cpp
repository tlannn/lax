#include "common/CompileTimeException.h"

CompileTimeException::CompileTimeException(std::string file, const int line,
    const int col, std::string message, std::string type) :
    Exception(std::move(message), std::move(type)),
    m_file(std::move(file)),
    m_line(line),
    m_col(col) {}

const char* CompileTimeException::what() const noexcept {
    return (new std::string(
        m_file + ":" +
        std::to_string(m_line) + ":" + std::to_string(m_col) + ": " +
        Exception::what())
    )->c_str();
}

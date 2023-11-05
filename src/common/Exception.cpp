#include "common/Exception.h"

Exception::Exception(std::string message, std::string type) : std::exception(),
    m_message(std::move(message)),
    m_type(std::move(type)) {}

const char* Exception::what() const noexcept {
    if (m_type.empty())
        return m_message.c_str();

    return (new std::string(m_type + ": " + m_message))->c_str();
}

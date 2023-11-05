#ifndef LAX_EXCEPTION_H
#define LAX_EXCEPTION_H

#include <exception>
#include <string>

/**
 * @class Exception
 * @brief Base class for all exceptions in Lax.
 */
class Exception : public std::exception {
public:
    /**
     * @brief Class constructor.
     * @param message The exception message.
     * @param type The type of exception.
     */
    explicit Exception(std::string message, std::string type = "");

    /**
     * @brief Gets the exception message.
     * @return The exception message.
     */
    const char* what() const noexcept override;

protected:
    const std::string m_message;
    const std::string m_type;
};

#endif // LAX_EXCEPTION_H

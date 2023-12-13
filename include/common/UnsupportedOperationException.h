#ifndef LAX_UNSUPPORTEDOPERATIONEXCEPTION_H
#define LAX_UNSUPPORTEDOPERATIONEXCEPTION_H

#include "common/Exception.h"

class UnsupportedOperationException : Exception {
public:
    /**
     * Class constructor
     * @param message the exception message
     */
    UnsupportedOperationException(std::string message);

    /**
     * Get string identifying exception
     * @return the string
     */
    const char* what() const noexcept override;
};

#endif // LAX_UNSUPPORTEDOPERATIONEXCEPTION_H

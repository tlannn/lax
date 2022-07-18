#ifndef LAX_NUM_H
#define LAX_NUM_H

#include <string>

#include "token.h"

/**
 * Token for a numeric value in the language
 */
class Num : public Token {
public:
    /**
     * Class constructor
     *
     * @param v the numeric value
     */
    Num(int value, int line, int col);

    /**
     * Getter for the numeric value of the token
     *
     * @return the value
     */
    int getValue() const;

    /// Stringify the token
    std::string toString() const override;
};

#endif //LAX_NUM_H

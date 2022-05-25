#ifndef LAX_OP_H
#define LAX_OP_H

#include <string>

#include "token.h"

/**
 * Token for an operator in the language
 */
class Op : public Token {
public:
    /**
     * Class constructor
     *
     * @param op the operator
     */
    explicit Op(const std::string &op);

    /// Stringify the token
    std::string toString() const override;
};

#endif //LAX_OP_H

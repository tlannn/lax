#include "op.h"

/// Op constructor
Op::Op(const std::string &op) : Token(op, TokenType::OP) {}

/// Stringify the token
std::string Op::toString() const {
    return _text;
}

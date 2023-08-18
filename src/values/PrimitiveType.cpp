#include "values/PrimitiveType.h"
#include "tokens/Token.h"

PrimitiveType PrimitiveType::BOOLEAN = PrimitiveType();
PrimitiveType PrimitiveType::INTEGER = PrimitiveType();
PrimitiveType PrimitiveType::STRING = PrimitiveType();
PrimitiveType PrimitiveType::VOID = PrimitiveType();

PrimitiveType::PrimitiveType() :
    LaxType(PRIMITIVE) {}

PrimitiveType* PrimitiveType::getType(Token* token) {
    const std::string lexeme = token->toString();

    if (lexeme == PrimitiveType::toString(PrimitiveType::BOOLEAN))
        return &PrimitiveType::BOOLEAN;

    else if (lexeme == PrimitiveType::toString(PrimitiveType::INTEGER))
        return &PrimitiveType::INTEGER;

    else if (lexeme == PrimitiveType::toString(PrimitiveType::STRING))
        return &PrimitiveType::STRING;

    else if (lexeme == PrimitiveType::toString(PrimitiveType::VOID))
        return &PrimitiveType::VOID;

    return nullptr;
}

std::string PrimitiveType::toString(const PrimitiveType& t) {
    // Compare values address because all types instances are equal, since
    // they have no members to differentiate them
    if (&t == &PrimitiveType::BOOLEAN)
        return "bool";
    else if (&t == &PrimitiveType::INTEGER)
        return "int";
    else if (&t == &PrimitiveType::STRING)
        return "string";
    else if (&t == &PrimitiveType::VOID)
        return "void";

    return "";
}

std::string PrimitiveType::toString() const {
    return PrimitiveType::toString(*this);
}

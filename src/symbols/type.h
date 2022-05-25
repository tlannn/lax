#ifndef LAX_TYPE_H
#define LAX_TYPE_H

#include "lexer/tokentype.h"
#include "lexer/word.h"

class Type : public Word {
public:
    static Type INT; // Basic type 'int' for integers
    static Type BOOL; // Basic type 'bool' for booleans

    /**
     * Class constructor
     *
     * @param word the word representing the type
     * @param type the type of the token
     * @param size the size in bytes for the type
     */
    Type(const std::string &word, TokenType type, int size);

    /**
     * Getter for the type size
     *
     * @return the size in bytes of the type
     */
    int getSize() const;

    /**
     * Overload the equality operator to compare two types
     *
     * @param t1 the first type to compare
     * @param t2 the second type to compare
     * @return true if the two types are equal
     */
    friend bool operator== (const Type &t1, const Type &t2);

    /**
     * Overload the not equal operator to compare two types
     *
     * @param t1 the first type to compare
     * @param t2 the second type to compare
     * @return true if the two types are not equal
     */
    friend bool operator!= (const Type &t1, const Type &t2);

protected:
    int _size;
};

#endif // LAX_TYPE_H

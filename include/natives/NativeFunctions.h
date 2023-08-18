#ifndef LAX_NATIVEFUNCTIONS_H
#define LAX_NATIVEFUNCTIONS_H

#include <iostream>

#include "values/Value.h"

/**
 * Native function that prints a Lax value followed by an newline in the
 * standard output stream.
 *
 * @param argCount the number of arguments passed to the function call.
 * @param args the arguments of the function.
 * @return the null value.
 */
Value printNative(int argCount, Value* args);

#endif //LAX_NATIVEFUNCTIONS_H

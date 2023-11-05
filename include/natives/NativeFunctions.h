#ifndef LAX_NATIVEFUNCTIONS_H
#define LAX_NATIVEFUNCTIONS_H

#include <iostream>

#include "values/Value.h"

/**
 * @brief Prints a value to the standard output.
 *
 * This function is used as a native function in Lax.
 *
 * It prints a value to the standard output and appends a newline character to
 * the end of the output. The value is converted to a string before being printed.
 *
 * @param argCount the number of arguments passed to the function.
 * @param args the arguments passed to the function.
 * @return the null value.
 */
Value printNative(int argCount, Value* args);

#endif //LAX_NATIVEFUNCTIONS_H

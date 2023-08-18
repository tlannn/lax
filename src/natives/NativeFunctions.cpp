#include "natives/NativeFunctions.h"

/// Native function that prints a Lax value followed by an newline in the
/// standard output stream.
Value printNative(int argCount, Value* args) {
    for (int i = 0; i < argCount; ++i) {
        std::cout << Value::toString(args[i]);
    }

    std::cout << std::endl;

    return Value::null();
}

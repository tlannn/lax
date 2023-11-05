#include "natives/NativeFunctions.h"

Value printNative(int argCount, Value* args) {
    for (int i = 0; i < argCount; ++i) {
        std::cout << Value::toString(args[i]);
    }

    std::cout << std::endl;

    return Value::null();
}

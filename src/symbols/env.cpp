#include "env.h"

/// Class constructor
Env::Env() : _previous(nullptr) {}

/// Class constructor
Env::Env(Env *previous) : _previous(previous) {}

/// Define a symbol in the environment
void Env::put(Symbol *symbol) {
    _table.define(symbol);
}

/// Look for a symbol defined in the environment or previous environment
Symbol* Env::get(std::string str) {
    for (Env *env = this; env != nullptr; env = env->_previous) {
        Symbol* found = env->_table.lookup(str);
        if (found != nullptr) return found;
    }

    return nullptr;
}

#include <iostream>
#include "env.h"

/// Class constructor
Env::Env() : _previous(nullptr) {
	std::cout << "new env: " << this << " (prev: " << _previous << ")" << std::endl;
}

/// Class constructor
Env::Env(Env *previous) : _previous(previous) {}

/// Define a symbol in the environment
void Env::put(Symbol *symbol) {
    _table.define(symbol);
}

/// Look for a symbol defined in the environment or previous environment
Symbol* Env::get(std::string str) {
	std::cout << "start: " << std::endl;
    for (Env *env = this; env != nullptr; env = env->getPreviousEnv()) {
		std::cout << "env: " << env << std::endl;
        Symbol* found = env->_table.lookup(str);
        if (found != nullptr) return found;
    }

    return nullptr;
}

/// Return the previous environment saved. May be used to go back to a previous
/// state of the environment
Env* Env::getPreviousEnv() {
	return _previous;
}

#include "env.h"

/// Class constructor
Env::Env() : _previous(nullptr) {}

/// Class constructor
Env::Env(Env *previous) : _previous(previous) {}

/// Class destructor
Env::~Env() {
	delete _previous;
}

/// Define a symbol in the environment
void Env::put(std::unique_ptr<Symbol> symbol) {
    _table.define(std::move(symbol));
}

/// Look for a symbol defined in the environment or previous environment
Symbol* Env::get(std::string str) {
    for (Env *env = this; env != nullptr; env = env->getPreviousEnv()) {
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

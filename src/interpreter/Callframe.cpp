#include "interpreter/Callframe.h"

/// Class constructor
CallFrame::CallFrame() : _previous(nullptr) {}

/// Class constructor
CallFrame::CallFrame(CallFrame *previous) : _previous(previous) {}

/// Get a value associated to a name
Value CallFrame::get(const std::string &varName) {
	auto it = _memory.find(varName);

	// Return the value if found
	if (it != _memory.end())
		return it->second;

	// If not found, search in the enclosing frames
	if (_previous)
		return _previous->get(varName);

	throw RuntimeError("Undefined variable '" + varName + "'");
}

/// Register a value associated to a name
void CallFrame::set(const std::string &varName, Value value) {
	_memory[varName] = value;
}

/// Getter for the previous call frame
CallFrame *CallFrame::getPrevious() {
	return _previous;
}

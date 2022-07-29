#ifndef LAX_CALLFRAME_H
#define LAX_CALLFRAME_H

#include <map>
#include <memory>
#include <string>

#include "RuntimeError.h"
#include "objects/Object.h"

/**
 * Class that tracks variables and functions declared in call frame
 *
 * A new call frame is created each time a call is performed. This creates a
 * scope in which variables and functions lives. When the call end, the frame
 * is deleted with its associated objects
 */
class CallFrame {
public:
	/**
	 * Class constructor
	 */
	CallFrame();

	/**
	 * Class constructor
	 * @param previous pointer to the previous call frame
	 */
	explicit CallFrame(CallFrame *previous);

	/**
	 * Class destructor
	 */
	~CallFrame() = default;

	/**
	 * Get a value associated to a name
	 * @param varName the name registered
	 * @return the value associated
	 */
	Value get(const std::string &varName);

	/**
	 * Register a value associated to a name
	 * @param varName the name registered
	 * @param value the value associated
	 */
	void set(const std::string &varName, Value value);

	/**
	 * Getter for the previous call frame
	 * @return the previous call frame
	 */
	CallFrame* getPrevious();

private:
	CallFrame *_previous;
	std::map<std::string, Value> _memory;
};

#endif // LAX_CALLFRAME_H

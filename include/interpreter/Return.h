#ifndef LAX_RETURN_H
#define LAX_RETURN_H

#include "common/Exception.h"
#include "common/Value.h"

/**
 * Exception simulating a return in a function
 *
 * When thrown, the exception will unwind function calls until caught. If so,
 * then program flow will continue with the value returned.
 *
 * This class is not intended to raise exceptions and will return an emtpy error
 * message when method what() is called
 */
class Return : public Exception {
public:
	/**
	 * Class constructor
	 * @param value the value returned
	 */
	explicit Return(Value value);

	/**
	 * Getter for the value returned
	 * @return the value
	 */
	Value getValue();

private:
	Value _value;
};

#endif // LAX_RETURN_H

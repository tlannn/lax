#ifndef LAX_OBJFUNCTION_H
#define LAX_OBJFUNCTION_H

#include <memory>
#include <string>
#include <vector>

#include "common/Chunk.h"
#include "objects/Object.h"

// Forward declarations
class ObjString;

/**
 * Function object in Lax.
 *
 * A function is a block of reusable code. It can take input data called
 * parameters or arguments, and use them to accomplish a specific task.
 * The task performed is specified by the body of the function ; it is a
 * sequence of instructions.
 *
 * Finally, a function can return a value. If no value is explicitly returned,
 * then the null value is automatically returned.
 */
class ObjFunction : public Object {
public:
	/**
	 * Class constructor.
	 *
	 * @param name the name of the function
	 * @param arity the number of parameters that the function takes
	 */
	explicit ObjFunction(ObjString *name, int arity = 0);

	/**
	 * Getter for the number of parameters of the function.
	 *
	 * @return the number of parameters.
	 */
	int arity() const;

	/// Increment the number of upvalues used in the function.
	void incrementUpvalueCount();

	/**
	 * Return the number of upvalues used in the function.
	 *
	 * @return the number of upvalues used.
	 */
	int getUpvalueCount() const;

	/**
	 * Return a pointer to the chunk of bytecode that depicts the function.
	 *
	 * @return a pointer to the function bytecode chunk.
	 */
	Chunk* getChunk();

	/// Return a string representation of the function.
	std::string toString() override;

private:
	ObjString *_name;
	int _arity;
	int _upvalueCount;
	Chunk _chunk;
};

#define AS_FUNCTION(value)	((dynamic_cast<ObjFunction*>(AS_OBJ(value))))

#endif // LAX_OBJFUNCTION_H

#ifndef LAX_OBJFUNCTION_H
#define LAX_OBJFUNCTION_H

#include <memory>
#include <vector>

#include "Callable.h"
#include "ast/FunNode.h"
#include "common/Value.h"
#include "interpreter/Callframe.h"
#include "interpreter/Interpreter.h"

/**
 * Function object in Lax
 *
 * A function is a block or reusable code. It can take input data called
 * parameters or arguments, and use them to accomplish a specific task.
 * The task performed is specified by the body of the function ; it is a
 * sequence of instructions.
 * Finally, a function can return a value. If no value is explicitly returned,
 * then the null value is automatically returned.
 */
class ObjFunction : public Object, Callable {
public:
	/**
	 * Class constructor
	 * @param declaration the node representing the function declaration
	 */
	explicit ObjFunction(FunNode *declaration);

	/**
	 * Getter for the number of parameters of the function
	 * @return the number of parameters
	 */
	int arity() override;

	/**
	 * Call the object and execute its body
	 * @param interpreter
	 * @param env
	 * @param args
	 * @return
	 */
	Value call(Interpreter *interpreter, CallFrame *env, std::vector<Value> args) override;

	/**
	 * Return a string representation of the function
	 */
	std::string toString() override;

private:
	FunNode *_declaration;
};

#define AS_FUNCTION(value)	((dynamic_cast<Function*>(AS_OBJ(value))))

#endif // LAX_OBJFUNCTION_H

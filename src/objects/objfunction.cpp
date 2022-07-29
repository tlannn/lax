#include "objfunction.h"

/// Class constructor
ObjFunction::ObjFunction(FunNode *declaration) : Object(ObjType::OBJ_FUNCTION), _declaration(declaration) {}

/// Getter for the number of parameters of the function
int ObjFunction::arity() {
	return static_cast<int>(_declaration->getParams().size());
}

/// Call the object and execute its body
Value ObjFunction::call(Interpreter *interpreter, CallFrame *frame, std::vector<Value> args) {
	// Add all parameters value to the function call frame
	for (int i = 0; i < _declaration->getParams().size(); ++i) {
		frame->set(_declaration->getParams().at(i)->getVarName()->toString(), args.at(i));
	}

	// Execute the function body and catch any return
	try {
		interpreter->executeBlock(_declaration->getBody(), frame);
	} catch (Return &e) {
		return e.getValue(); // Return the value from the function
	}

	// Return null by default
	return NULL_VAL;
}

/// Return a string representation of the function
std::string ObjFunction::toString() {
	return "<fn " + _declaration->getName()->toString() + ">";
}

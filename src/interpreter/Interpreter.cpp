#include "interpreter/Interpreter.h"

/// Class constructor
Interpreter::Interpreter(ASTNode *ast) : _ast(ast), _result(NULL_VAL), _frame(new CallFrame()) {}

/// Interpret the code parsed by the parser
void Interpreter::interpret() {
	try {
		_ast->accept(this);
	} catch (RuntimeError &e) {
		Logger::error(e.what());
	}
}

/// Visit an ExprNode and determine the value to which it can be reduced
void Interpreter::visit(ExprNode *node) {
    return node->accept(this);
}

/// Visit a BinOpNode and compute the operation represented by the node
void Interpreter::visit(BinOpNode *node) {
	Token* op = node->getOperator();

	// Determine the value of the left operand
	visit(node->getLeft());
	Value v = INT_VAL(1);

	if (!IS_INT(_result))
		throw RuntimeError("incompatible value", "error");

	int left = AS_INT(_result);

	// Determine the value of the right operand
	visit(node->getRight());

	if (!IS_INT(_result))
		throw RuntimeError("incompatible value", "error");

	int right = AS_INT(_result);

	// Compute the result
	switch (op->getType()) {
		case TokenType::PLUS: {
			_result = INT_VAL(left + right);
			break;
		}
		case TokenType::MINUS: {
			_result = INT_VAL(left - right);
			break;
		}
		case TokenType::STAR: {
			_result = INT_VAL(left * right);
			break;
		}
		case TokenType::SLASH: {
			_result = INT_VAL(left / right);
			break;
		}
		default:
			_result = NULL_VAL;
			break;
	}
}

/// Visit a LogicalNode and compute the boolean value represented by the
/// boolean expression
void Interpreter::visit(LogicalNode *node) {
	Token* op = node->getOperator();

	// Determine the value of the left operand
	visit(node->getLeft());

	if (!IS_BOOL(_result))
		throw RuntimeError("incompatible value", "error");

	bool left = AS_BOOL(_result);

	if (op->getType() == TokenType::OR) {
		if (left) _result = BOOL_VAL(left);
	} else if (op->getType() == TokenType::AND) {
		if (!left) _result = BOOL_VAL(left);
	}

	visit(node->getRight());
}

/// Visit a RelationalNode and compute the resulting boolean value
/// according to the truthiness of the equality or inequality
void Interpreter::visit(RelationalNode *node) {
	Token* op = node->getOperator();

	// Determine the value of the left operand
	visit(node->getLeft());

	if (!IS_INT(_result))
		throw RuntimeError("incompatible value", "error");

	int left = AS_INT(_result);

	// Determine the value of the right operand
	visit(node->getRight());

	if (!IS_INT(_result))
		throw RuntimeError("incompatible value", "error");

	int right = AS_INT(_result);

	switch (op->getType()) {
		case TokenType::EQ:
			_result = BOOL_VAL(left == right);
			break;
		case TokenType::NEQ:
			_result = BOOL_VAL(left != right);
			break;
		case TokenType::SL:
			_result = BOOL_VAL(left < right);
			break;
		case TokenType::LE:
			_result = BOOL_VAL(left <= right);
			break;
		case TokenType::SG:
			_result = BOOL_VAL(left > right);
			break;
		case TokenType::GE:
			_result = BOOL_VAL(left >= right);
			break;
		default:
			_result = NULL_VAL;
			break;
	}
}

/// Visit a LiteralNode and determine the literal value represented
void Interpreter::visit(LiteralNode *node) {
	_result = node->getValue();
}

/// Visit an Id and determine the value of the variable defined with this
/// identifier
void Interpreter::visit(Id *node) {
	_result = _frame->get(node->getName()->toString());
}

/// Visit a CallNode and evaluate the call
void Interpreter::visit(CallNode *node) {
	visit(node->getCallee());

	if (!IS_CLOSURE(_result))
		throw RuntimeError("Error on function call");

	auto *function = AS_CLOSURE(_result)->getFunction();

	// Compute all arguments
	std::vector<Value> args;
	for (auto& arg : node->getArgs()) {
		visit(arg.get());
		args.push_back(_result);
	}

	// Check that the number of arguments is the same as in the function declaration
	if (node->getArgs().size() != function->arity())
		throw RuntimeError("Function " + function->toString() + " expected " +
							std::to_string(function->arity()) + " arguments but got " +
							std::to_string(node->getArgs().size()));

	// Execute the function call
	_result = function->call(this, new CallFrame(_frame), std::move(args));
}

/// Visit an UnaryNode and determine the resulting literal value
void Interpreter::visit(UnaryNode *node) {
	visit(node->getExpr());
	TokenType operatorType = node->getOperator()->getType();

	if (operatorType == TokenType::BANG) {
		// Determine the value of the expression associated
		visit(node->getExpr());

		if (!IS_BOOL(_result))
			throw RuntimeError("incompatible value", "error");

		bool result = AS_BOOL(_result);

		_result = BOOL_VAL(!result);
	}

	else if (operatorType == TokenType::PLUS || operatorType == TokenType::MINUS) {
		// Determine the value of the expression associated
		visit(node->getExpr());

		if (!IS_INT(_result))
			throw RuntimeError("incompatible value", "error");

		int result = AS_INT(_result);

		_result = INT_VAL(-result);
	}

	else _result = NULL_VAL;
}

/// Visit a StmtNode and execute the statement
void Interpreter::visit(StmtNode *node) {
    node->accept(this);
}

/// Visit a BlockNode and execute the sequence of statements inside it
void Interpreter::visit(BlockNode *node) {
	executeBlock(node, new CallFrame(_frame));
}

/// Execute the instructions inside a block
void Interpreter::executeBlock(BlockNode *node, CallFrame *frame) {
	CallFrame *previousFrame = _frame;

	try {
		_frame = frame;
		visit(node->getSequence());
	} catch (RuntimeError &e) {
		_frame = previousFrame;
		delete frame;

		throw;
	}

	_frame = previousFrame;
	delete frame;
}

/// Visit a SeqNode and execute all the statements inside it
void Interpreter::visit(SeqNode *node) {
	auto& stmts = node->getStatements();

	for (int i = 0; i < stmts.size(); ++i) {
		visit(stmts[i].get());
	}
}

/// Visit a DeclNode and declare a variable
void Interpreter::visit(DeclNode *node) {
	Value value = NULL_VAL;

	if (node->getRValue() != nullptr) {
		visit(node->getRValue());
		value = _result;
	}

	_frame->set(node->getId()->toString(), value);
}

/// Visit an AssignNode and assign a new value to a variable
void Interpreter::visit(AssignNode *node) {
	visit(node->getExpr());
	_frame->set(node->getName(), _result);
}

/// Visit a FunNode and save its function definition
void Interpreter::visit(FunNode *node) {
	// Save the function definition in the current call frame
	_frame->set(node->getName()->toString(), OBJ_VAL(new ObjClosure(new ObjFunction(node))));

	// The result of the definition is null
	_result = NULL_VAL;
}

/// Visit a ConditionalNode and execute the 'then' statement referenced
/// if the condition is evaluated to true, otherwise execute the 'else'
/// statement if there is one
void Interpreter::visit(ConditionalNode *node) {
	// Determine the value of the condition
	visit(node->getConditionExpression());

	if (!IS_BOOL(_result))
		throw RuntimeError("incompatible value", "error");

	bool result = AS_BOOL(_result);

	if (result)
		visit(node->getThenStatement());

	else if (node->getElseStatement())
		visit(node->getElseStatement());
}

/// Visit a ReturnNode and return from a function
void Interpreter::visit(ReturnNode *node) {
	_result = NULL_VAL;

	if (node->getValue())
		visit(node->getValue());

	throw Return(_result);
}

/// Visit a StmtPrintNode and print the result of an expression
void Interpreter::visit(StmtPrintNode *node) {
    visit(node->getExpr());

	std::string result;

	if (IS_INT(_result))
		result = std::to_string(AS_INT(_result));

	else if (IS_BOOL(_result))
		result = AS_BOOL(_result) ? "true" : "false";

	else if (IS_OBJ(_result))
		result = AS_CPPSTRING(_result);

	else if (IS_NULL(_result))
		result = "null";

    std::cout << result << std::endl;
}

/// Visit a StmtExpressionNode and reduce an expression
void Interpreter::visit(StmtExpressionNode *node) {
	visit(node->getExpr());
}

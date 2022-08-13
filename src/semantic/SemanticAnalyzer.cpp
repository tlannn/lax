#include "semantic/SemanticAnalyzer.h"
#include "objects/Variable.h"

/// Class constructor
SemanticAnalyzer::SemanticAnalyzer(ASTNode *ast) :
		_ast(ast), _env(new Env()), _resultType(ValueType::VAL_NULL), _errors(false) {
	// Add the native function 'print' to the symbol table
	std::vector<std::unique_ptr<VarSymbol>> args;
	args.push_back(std::make_unique<VarSymbol>("message", ValueType::VAL_INT));
	auto printFn = std::make_unique<FunSymbol>("print", std::move(args), ValueType::VAL_NULL);
	_env->put(std::move(printFn));
}

/// Class destructor
SemanticAnalyzer::~SemanticAnalyzer() {
	delete _env;
}

/// Analyze semantically the code parsed by the parser
void SemanticAnalyzer::analyze() {
	_ast->accept(this);
}

/// Return whether errors occurred during semantic analysis
bool SemanticAnalyzer::hadErrors() const {
	return _errors;
}

/// Return an exception on a specific token
SemanticError SemanticAnalyzer::error(
		Token *token, const std::string &message, const std::string &type) {
	_errors = true;
	return SemanticError(Lexer::currentFile, token->getLine(), token->getColumn(), message, type);
}

/// Report an error to inform the user
void SemanticAnalyzer::report(const SemanticError &err) {
	Logger::error(err.what());
}

/// Visit an expression node and determine the type of the value to which it
/// has been reduced
void SemanticAnalyzer::visit(ExprNode *node) {
	node->accept(this);
}

/// Visit an AssignNode and check that the new value is type-consistent, and
/// if needed, update the type of the variable symbol
void SemanticAnalyzer::visit(AssignNode *node) {
	std::string varName = node->getToken()->toString();
	VarSymbol *var = dynamic_cast<VarSymbol *>(_env->get(varName));

	if (!var) {
		report(error(node->getToken(),
					 "'" + varName + "' was not declared in this scope", "Undefined symbol"));
		visit(node->getExpr());
		return;
	}

	ValueType varType = var->getType();
	visit(node->getExpr());

	ValueType assignType = _resultType;

	if (varType == ValueType::VAL_NULL)
		var->setType(assignType);

	else if (assignType != varType)
		report(error(node->getExpr()->getToken(),
					 "Cannot convert '" + ValueType::toString(assignType) + "' to '" + ValueType::toString(varType) +
					 "'",
					 "TypeError"));
}

/// Visit a LogicalNode and set the type of the expression as boolean
void SemanticAnalyzer::visit(LogicalNode *node) {
	_resultType = ValueType::VAL_BOOL;
}

/// Visit a RelationalNode and set the type of the expression as boolean
void SemanticAnalyzer::visit(RelationalNode *node) {
	visit(node->getLeft());
	ValueType typeLeft = _resultType;

	visit(node->getRight());
	ValueType typeRight = _resultType;

	if (ValueType::isNumeric(typeLeft) && ValueType::isNumeric(typeRight) ||
		typeLeft == ValueType::VAL_BOOL && typeRight == ValueType::VAL_BOOL)
		_resultType = ValueType::VAL_BOOL;

	else report(error(node->getRight()->getToken(),
					 "Cannot compare type '" + ValueType::toString(typeRight) + "' with type '" + ValueType::toString
					 (typeLeft)
					 + "'",
					 "Bad Operand"));
}

/// Visit a BinOpNode and determine the type of the result computed by the
/// operation represented by the node
void SemanticAnalyzer::visit(BinOpNode *node) {
	Token* op = node->getOperator();

	visit(node->getLeft());
	ValueType typeLeft = _resultType;

	visit(node->getRight());
	ValueType typeRight = _resultType;

	_resultType = ValueType::max(typeLeft, *op, typeRight);

	if (_resultType == ValueType::VAL_NULL)
		report(error(node->getRight()->getToken(),
					 "Incompatible type '" + ValueType::toString(typeRight) + "' with type '" + ValueType::toString(typeLeft) +
					 "'",
					 "Bad Operand"));
}

/// Visit an UnaryNode and determine the type of the literal
void SemanticAnalyzer::visit(UnaryNode *node) {
	visit(node->getExpr());
	TokenType operatorType = node->getOperator()->getType();

	if (operatorType == TokenType::BANG)
		_resultType = ValueType::VAL_BOOL;
	else if ((operatorType == TokenType::PLUS || operatorType == TokenType::MINUS) && ValueType::isNumeric(_resultType))
		_resultType = _resultType;
	else
		report(error(node->getOperator(),
					 "Expected numeric value after '" + node->getOperator()->toString(),
					 "Unexpected symbol"));
}

/// Visit a CallNode and check if the function called is defined
void SemanticAnalyzer::visit(CallNode *node) {
	std::string funName = node->getCallee()->getToken()->toString();
//	FunSymbol *fun = dynamic_cast<FunSymbol *>(_env->get(funName));
	Symbol *fun = _env->get(funName);

	if (!fun) {
		report(error(node->getCallee()->getToken(),
					 "'" + funName + "' was not declared in this scope", "Undefined symbol"));
		return;
	}

//	if (node->getArgs().size() != fun->getArgs().size())
//		report(error(node->getCallee()->getToken(),
//					 "Function '" + node->getCallee()->getToken()->toString() + "()' expected " +
//					 std::to_string(fun->getArgs().size()) + " arguments but got " +
//					 std::to_string(node->getArgs().size()),
//					 "Error"));

//	for (int i = 0; i < fun->getArgs().size(); ++i) {
//		visit(node->getArgs()[i].get());
//
//		if (_resultType != fun->getArgs()[i]->getType())
//			report(error(node->getArgs()[i]->getToken(),
//						 "Expected type '" + ValueType::toString(fun->getArgs()[i]->getType()) +
//						 "' but got '" + ValueType::toString(_resultType) + "'",
//						 "TypeMismatch"));
//	}
}

/// Visit a LiteralNode and determine the type of the literal
void SemanticAnalyzer::visit(LiteralNode *node) {
	_resultType = node->getValue().type;
}

/// Visit an IdNode and determine the type of the value associated
void SemanticAnalyzer::visit(IdNode *node) {
	std::string name = node->getName()->toString();
	Symbol* sym = _env->get(name);

	if (!sym) {
		report(error(node->getName(),
					 "'" + name + "' was not declared in this scope",
					 "Undefined symbol"));

		_resultType = ValueType::VAL_NULL;
	}

	else
		_resultType = sym->getType();
}

/// Visit a StmtNode and check semantics inside it
void SemanticAnalyzer::visit(StmtNode *node) {
    node->accept(this);
}

/// Visit a BlockNode and check semantics in the sequence of statements
/// inside it
void SemanticAnalyzer::visit(BlockNode *node) {
	_env = new Env(_env);
	visit(node->getSequence());
	_env = _env->getPreviousEnv();
}

/// Visit a SeqNode and check semantics in all statements inside it
void SemanticAnalyzer::visit(SeqNode *node) {
	auto& stmts = node->getStatements();

	for (int i = 0; i < stmts.size(); ++i)
		visit(stmts[i].get());
}

/// Visit a DeclNode and create a symbol associated to the variable created
/// to keep track of its type
void SemanticAnalyzer::visit(DeclNode *node) {
	std::string varName = node->getId()->toString();
	ValueType varType = node->getType();

	// Check if variable is already declared in the scope
	if (_env->get(varName)) {
		report(error(node->getId().get(),
					 "'" + varName + "' has already been declared in this scope",
					 "Error"));

		// Change varType to the type of the variable already declared
		varType = _env->get(varName)->getType();
	}

	// Evaluate assigned expression, if any
	if (node->getRValue() != nullptr) {
		visit(node->getRValue());
		ValueType assignType = _resultType;

		if (varType == ValueType::VAL_NULL) {
			varType = assignType;
		}

		else if (assignType != varType)
			report(error(node->getRValue()->getToken(),
				  "Cannot convert type '" + ValueType::toString(assignType) + "' to '" + ValueType::toString(varType)
				  + "'",
				  "TypeError"));
	}

	if (!_env->get(varName))
		_env->put(std::make_unique<VarSymbol>(varName, varType));
}

/// Visit a ConditionalNode and check symbols in both branches 'then' and 'else'
void SemanticAnalyzer::visit(ConditionalNode *node) {
	visit(node->getConditionExpression());

	_env = new Env(_env);
	visit(node->getThenStatement());
	_env = _env->getPreviousEnv();

	if (node->getElseStatement()) {
		_env = new Env(_env);
		visit(node->getElseStatement());
		_env = _env->getPreviousEnv();
	}
}

/// Visit a FunNode and define a function in the environment
void SemanticAnalyzer::visit(FunNode *node) {
	std::string funName = node->getName()->toString();

	// Check if function does not already exist
	if (_env->get(funName)) {
		report(error(node->getName(),
					 "Redefinition of function '" + funName + "()'",
					 "Error"));
	}

	_env = new Env(_env);

	std::vector<std::unique_ptr<VarSymbol>> params;
	for (auto& param : node->getParams()) {
		auto varName = param->getVarName()->toString();
		auto varType = param->getType();

		params.push_back(std::make_unique<VarSymbol>(varName, varType));
		_env->put(std::make_unique<VarSymbol>(varName, varType));
	}

	if (!_env->getPreviousEnv()->get(funName))
		_env->getPreviousEnv()->put(std::make_unique<FunSymbol>(funName, std::move(params), node->getType()));

	visit(node->getBody());

	_env = _env->getPreviousEnv();
}

/// Visit a ReturnNode and exit a function call by returning a value
void SemanticAnalyzer::visit(ReturnNode *node) {}

/// Visit a StmtExpressionNode and check semantics in the expression
void SemanticAnalyzer::visit(StmtExpressionNode *node) {
	visit(node->getExpr());
}

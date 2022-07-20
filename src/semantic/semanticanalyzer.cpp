#include "semanticanalyzer.h"

/// Class constructor
SemanticAnalyzer::SemanticAnalyzer(ASTNode *ast) :
	_ast(ast), _env(new Env()), _resultType(Type::NONE), _errors(false) {}

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

/// Evaluate an expression node and return the value to which it has been reduced
void SemanticAnalyzer::visit(ExprNode *node) {
	node->accept(this);
}

/// Visit a BinOpNode and compute the operation represented by the node
void SemanticAnalyzer::visit(BinOpNode *node) {
	Token* op = node->getToken();

	visit(node->getLeft());
	Type typeLeft = _resultType;

	visit(node->getRight());
	Type typeRight = _resultType;

	_resultType = Type::max(typeLeft, *op, typeRight);

	if (_resultType == Type::NONE)
		report(error(node->getRight()->getToken(),
					"Incompatible type '" + typeRight.toString() + "' with type '" + typeLeft.toString() + "'",
					"Bad Operand"));
}

/// Visit a LogicalNode and return the boolean value represented by the boolean expression
void SemanticAnalyzer::visit(LogicalNode *node) {
	_resultType = Type::BOOL;
}

/// Visit a RelationalNode and return a boolean value according to the truthiness of the equality or inequality
void SemanticAnalyzer::visit(RelationalNode *node) {
	visit(node->getLeft());
	Type typeLeft = _resultType;

	visit(node->getRight());
	Type typeRight = _resultType;

	if (Type::numeric(typeLeft) && Type::numeric(typeRight) ||
		typeLeft == Type::BOOL && typeRight == Type::BOOL)
		_resultType = Type::BOOL;

	else report(error(node->getRight()->getToken(),
					 "Cannot compare type '" + typeRight.toString() + "' with type '" + typeLeft.toString() + "'",
					 "Bad Operand"));
}

/// Visit a LiteralNode and return the literal value represented
void SemanticAnalyzer::visit(LiteralNode *node) {
	_resultType = node->getType();
}

/// Visit an Id (identifier) and return the value of the variable defined with this identifier
void SemanticAnalyzer::visit(Id *node) {
	std::string varName = node->getToken()->toString();
	VarSymbol *varSym = dynamic_cast<VarSymbol *>(_env->get(varName));

	if (!varSym) {
		report(error(node->getToken(),
					 "'" + varName + "' was not declared in this scope",
					 "Undefined symbol"));

		_resultType = Type::NONE;
	}

	else
		_resultType = varSym->getType();
}

/// Visit an unary expression and return the literal value
void SemanticAnalyzer::visit(UnaryNode *node) {
	visit(node->getExpr());
	TokenType operatorType = node->getToken()->getType();

	if (operatorType == TokenType::BANG)
		_resultType = Type::BOOL;
	else if ((operatorType == TokenType::PLUS || operatorType == TokenType::MINUS) && Type::numeric(_resultType))
		_resultType = _resultType;
	else
		report(error(node->getToken(),
					 "Expected numeric value after '" + node->getToken()->toString(),
					 "Unexpected symbol"));
}

/// Execute a statement node
void SemanticAnalyzer::visit(StmtNode *node) {
    node->accept(this);
}

/// Visit a BlockNode and execute the sequence of statements inside it
void SemanticAnalyzer::visit(BlockNode *node) {
	_env = new Env(_env);
	visit(node->getSequence());
	_env = _env->getPreviousEnv();
}

/// Visit a SeqNode and execute all the statements inside it
void SemanticAnalyzer::visit(SeqNode *node) {
	auto& stmts = node->getStatements();

	for (int i = 0; i < stmts.size(); ++i)
		visit(stmts[i].get());
}

/// Visit a DeclNode and declare a variable
void SemanticAnalyzer::visit(DeclNode *node) {
	std::string varName = node->getId()->toString();
	Type varType = node->getType();

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
		Type assignType = _resultType;

		if (varType == Type::NONE) {
			varType = assignType;
		}

		else if (assignType != varType)
			report(error(node->getRValue()->getToken(),
				  "Cannot convert type '" + assignType.toString() + "' to '" + varType.toString() + "'",
				  "TypeError"));
	}

	if (!_env->get(varName))
		_env->put(std::make_unique<VarSymbol>(varName, varType));
}

/// Visit an AssignNode and assign a new value to a variable
void SemanticAnalyzer::visit(AssignNode *node) {
	std::string varName = node->getToken()->toString();
	VarSymbol *var = dynamic_cast<VarSymbol *>(_env->get(varName));

	if (!var) {
		report(error(node->getToken(),
					 "'" + varName + "' was not declared in this scope", "Undefined symbol"));
		visit(node->getExpr());
		return;
	}

	Type varType = var->getType();
	visit(node->getExpr());

	Type assignType = _resultType;

	if (varType == Type::NONE)
		var->setType(assignType);

	else if (assignType != varType)
		report(error(node->getExpr()->getToken(),
					 "Cannot convert '" + assignType.toString() + "' to '" + varType.toString() + "'",
					 "TypeError"));
}

/// Visit a ConditionalNode and execute the 'then' statement referenced if the condition
/// is evaluated to true, otherwise execute the 'else' statement if there is one
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

/// Visit a StmtPrintNode node and print the result of the expression in the statement
void SemanticAnalyzer::visit(StmtPrintNode *node) {
	visit(node->getExpr());
}

/// Visit a StmtExpressionNode node and compute the expression in the statement
void SemanticAnalyzer::visit(StmtExpressionNode *node) {
	visit(node->getExpr());
}

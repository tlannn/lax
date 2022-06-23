#include "semanticanalyzer.h"

/// Class constructor
SemanticAnalyzer::SemanticAnalyzer(Parser &parser) : _parser(parser), _resultType(Type::NONE) {}

/// Analyze semantically the code parsed by the parser
void SemanticAnalyzer::analyze() {
    StmtNode *tree = _parser.parse();
    execute(tree);
}

/// Evaluate an expression node and return the value to which it has been reduced
int SemanticAnalyzer::evaluate(ExprNode *node) {
    return node->accept(this);
}

/// Visit a BinOpNode and compute the operation represented by the node
int SemanticAnalyzer::visit(BinOpNode *node) {
	Token op = node->getToken();

	evaluate(node->getLeft());
	Type typeLeft = _resultType;

	evaluate(node->getRight());
	Type typeRight = _resultType;

	_resultType = Type::max(typeLeft, op, typeRight);

    return 0;
}

/// Visit a LogicalNode and return the boolean value represented by the boolean expression
int SemanticAnalyzer::visit(LogicalNode *node) {
	Token op = node->getToken();

	evaluate(node->getLeft());
	Type typeLeft = _resultType;

	evaluate(node->getRight());
	Type typeRight = _resultType;

	_resultType = Type::max(typeLeft, op, typeRight);

	return 0;
}

/// Visit a RelationalNode and return a boolean value according to the truthiness of the equality or inequality
int SemanticAnalyzer::visit(RelationalNode *node) {
	Token op = node->getToken();

	evaluate(node->getLeft());
	Type typeLeft = _resultType;

	evaluate(node->getRight());
	Type typeRight = _resultType;

	_resultType = Type::max(typeLeft, op, typeRight);

	return 0;
}

/// Visit a LiteralNode and return the literal value represented
int SemanticAnalyzer::visit(LiteralNode *node) {
	_resultType = node->getType();

	return 0;
}

/// Visit an Id (identifier) and return the value of the variable defined with this identifier
int SemanticAnalyzer::visit(Id *node) {
	std::string varName = node->getToken().toString();
	VarSymbol *varSym = dynamic_cast<VarSymbol*>(_env.get(varName));

	if (!varSym)
		throw std::runtime_error("'" + varName + "' is undefined.");

	_resultType = varSym->getType();

	return 0;
}

/// Execute a statement node
void SemanticAnalyzer::execute(StmtNode *node) {
    node->accept(this);
}

/// Visit a BlockNode and execute all the statements inside the block
void SemanticAnalyzer::visit(BlockNode *node) {
	std::vector<StmtNode*> stmts = node->getStatements();

	for (int i = 0; i < stmts.size(); ++i) {
		execute(stmts[i]);
	}
}

/// Visit a DeclNode and declare a variable
void SemanticAnalyzer::visit(DeclNode *node) {
	std::string varName = node->getName();
	Type varType = node->getType();

	if (_env.get(varName))
		throw std::runtime_error("Variable '" + varName + "' is already declared.");

	VarSymbol *varSym = new VarSymbol(varName, varType);
	_env.put(varSym);

	if (node->getRValue() != nullptr) {
		evaluate(node->getRValue());
		Type assignType = _resultType;

		if (assignType != varType)
			throw std::runtime_error("Cannot assign type '" + assignType.toString() + "' to variable '" +
									 varName + "' of type '" + varType.toString() + "'.");

		this->evaluate(node->getRValue());
	}
}

/// Visit an AssignNode and assign a new value to a variable
void SemanticAnalyzer::visit(AssignNode *node) {
	std::string varName = node->getLValue();
	VarSymbol *var = dynamic_cast<VarSymbol*>(_env.get(varName));

	if (!var)
		throw std::runtime_error("Variable '" + varName + "' is undefined.");

	Type varType = var->getType();
	evaluate(node->getRValue());
	Type assignType = _resultType;

	if (assignType != varType)
		throw std::runtime_error("Cannot assign type '" + assignType.toString() + "' to variable '" +
								 varName + "' of type '" + varType.toString() + "'.");

	evaluate(node->getRValue());
}

/// Visit a ConditionalNode and execute the 'then' statement referenced if the condition
/// is evaluated to true, otherwise execute the 'else' statement if there is one
void SemanticAnalyzer::visit(ConditionalNode *node) {
	evaluate(node->getConditionExpression());
	execute(node->getThenStatement());

	if (node->getElseStatement())
		execute(node->getElseStatement());
}

/// Visit a StmtPrintNode node and print the result of the expression in the statement
void SemanticAnalyzer::visit(StmtPrintNode *node) {
    evaluate(node->getExpr());
}

/// Visit a StmtExpressionNode node and compute the expression in the statement
void SemanticAnalyzer::visit(StmtExpressionNode *node) {
	evaluate(node->getExpr());
}

#include "interpreter.h"

/// Class constructor
Interpreter::Interpreter(ASTNode *ast) : _ast(ast), _result(Object::null) {}

/// Interpret the code parsed by the parser
void Interpreter::interpret() {
	try {
		_ast->accept(this);
	} catch (RuntimeError &e) {
		Logger::error(e.what());
	}
}

/// Evaluate an expression node and return the value to which it has been reduced
void Interpreter::visit(ExprNode *node) {
    return node->accept(this);
}

/// Visit a BinOpNode and compute the operation represented by the node
void Interpreter::visit(BinOpNode *node) {
	visit(node->getLeft());
	int left = _result.toInt();
	visit(node->getRight());
	int right = _result.toInt();
	Token *op = node->getToken();

	switch (op->getType()) {
		case TokenType::PLUS: {
			_result = Object(left + right);
			break;
		}
		case TokenType::MINUS: {
			_result = Object(left - right);
			break;
		}
		case TokenType::STAR: {
			_result = Object(left * right);
			break;
		}
		case TokenType::SLASH: {
			_result = Object(left / right);
			break;
		}
		default:
			_result = Object::null;
			break;
	}
}

/// Visit a LogicalNode and return the boolean value represented by the boolean expression
void Interpreter::visit(LogicalNode *node) {
	visit(node->getLeft());
	bool left = _result.toBool();
	Token *op = node->getToken();

	if (op->getType() == TokenType::OR) {
		if (left) _result = Object(left);
	} else if (op->getType() == TokenType::AND) {
		if (!left) _result = Object(left);
	}

	visit(node->getRight());
}

/// Visit a RelationalNode and return a boolean value according to the truthiness of the equality or inequality
void Interpreter::visit(RelationalNode *node) {
	visit(node->getLeft());
	int left = _result.toInt();
	visit(node->getRight());
	int right = _result.toInt();
	Token *op = node->getToken();

	switch (op->getType()) {
		case TokenType::EQ:
			_result = Object(left == right);
			break;
		case TokenType::NEQ:
			_result = Object(left != right);
			break;
		case TokenType::SL:
			_result = Object(left < right);
			break;
		case TokenType::LE:
			_result = Object(left <= right);
			break;
		case TokenType::SG:
			_result = Object(left > right);
			break;
		case TokenType::GE:
			_result = Object(left >= right);
			break;
		default:
			_result = Object::null;
			break;
	}
}

/// Visit a LiteralNode and return the literal value represented
void Interpreter::visit(LiteralNode *node) {
	_result = node->getValue();
}

/// Visit an Id (identifier) and return the value of the variable defined with this identifier
void Interpreter::visit(Id *node) {
	_result = _memory[node->getToken()->toString()];
}

/// Visit an unary expression and return the literal value
void Interpreter::visit(UnaryNode *node) {
	visit(node->getExpr());
	TokenType operatorType = node->getToken()->getType();

	if (operatorType == TokenType::BANG)
		_result = Object(!_result.toBool());

	else if (operatorType == TokenType::PLUS || operatorType == TokenType::MINUS)
		_result = Object(-_result.toInt());

	else _result = Object::null;
}

/// Execute a statement node
void Interpreter::visit(StmtNode *node) {
    node->accept(this);
}

/// Visit a BlockNode and execute the sequence of statements inside it
void Interpreter::visit(BlockNode *node) {
	visit(node->getSequence());
}

/// Visit a SeqNode and execute all the statements inside it
void Interpreter::visit(SeqNode *node) {
	std::vector<StmtNode*> stmts = node->getStatements();

	for (int i = 0; i < stmts.size(); ++i) {
		visit(stmts[i]);
	}
}

/// Visit a DeclNode and declare a variable
void Interpreter::visit(DeclNode *node) {
	if (node->getRValue() != nullptr) {
		visit(node->getRValue());
		_memory[node->getId()->toString()] = _result;
	}
}

/// Visit an AssignNode and assign a new value to a variable
void Interpreter::visit(AssignNode *node) {
	visit(node->getExpr());
	_memory[node->getToken()->toString()] = _result;
}

/// Visit a ConditionalNode and execute the 'then' statement referenced if the condition
/// is evaluated to true, otherwise execute the 'else' statement if there is one
void Interpreter::visit(ConditionalNode *node) {
	visit(node->getConditionExpression());

	if (_result.toBool())
		visit(node->getThenStatement());

	else if (node->getElseStatement())
		visit(node->getElseStatement());
}

/// Visit a StmtPrintNode node and print the result of the expression in the statement
void Interpreter::visit(StmtPrintNode *node) {
    visit(node->getExpr());
    std::cout << _result.toString() << std::endl;
}

/// Visit a StmtExpressionNode node and compute the expression in the statement
void Interpreter::visit(StmtExpressionNode *node) {
	visit(node->getExpr());
}

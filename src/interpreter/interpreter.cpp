#include "interpreter.h"

/// Class constructor
Interpreter::Interpreter(Parser &parser) : _parser(parser) {}

/// Interpret the code parsed by the parser
void Interpreter::interpret() {
    StmtNode *tree = _parser.parse();
    execute(tree);
}

/// Evaluate an expression node and return the value to which it has been reduced
int Interpreter::evaluate(ExprNode *node) {
    return node->accept(this);
}

/// Visit a BinOpNode and compute the operation represented by the node
int Interpreter::visit(BinOpNode *node) {
    int left = evaluate(node->getLeft());
    int right = evaluate(node->getRight());
    Token op = node->getToken();

    switch (op.toString().at(0)) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
    }

    return 0;
}

/// Visit a LogicalNode and return the boolean value represented by the boolean expression
int Interpreter::visit(LogicalNode *node) {
    int left = evaluate(node->getLeft());
    Token op = node->getToken();

    if (op.getType() == TokenType::OR) {
        if (left) return left;
    }
    else if (op.getType() == TokenType::AND) {
        if (!left) return left;
    }

    return evaluate(node->getRight());
}

/// Visit a RelationalNode and return a boolean value according to the truthiness of the equality or inequality
int Interpreter::visit(RelationalNode *node) {
    int left = evaluate(node->getLeft());
    int right = evaluate(node->getRight());
    Token op = node->getToken();

    switch (op.getType()) {
        case TokenType::EQ:
            return left == right;
        case TokenType::NEQ:
            return left != right;
        case TokenType::SL:
            return left < right;
        case TokenType::LE:
            return left <= right;
        case TokenType::SG:
            return left > right;
        case TokenType::GE:
            return left >= right;
    }

    return 0;
}

/// Visit a LiteralNode and return the literal value represented
int Interpreter::visit(LiteralNode *node) {
	return node->getValue();
}

/// Visit an Id (identifier) and return the value of the variable defined with this identifier
int Interpreter::visit(Id *node) {
	return _memory[node->getToken().toString()];
}

/// Execute a statement node
void Interpreter::execute(StmtNode *node) {
    node->accept(this);
}

/// Visit a BlockNode and execute all the statements inside the block
void Interpreter::visit(BlockNode *node) {
	std::vector<StmtNode*> stmts = node->getStatements();

	for (int i = 0; i < stmts.size(); ++i) {
		execute(stmts[i]);
	}
}

/// Visit a DeclNode and declare a variable
void Interpreter::visit(DeclNode *node) {
	if (node->getRValue() != nullptr) {
		_memory[node->getName()] = evaluate(node->getRValue());
	}
}

/// Visit an AssignNode and assign a new value to a variable
void Interpreter::visit(AssignNode *node) {
	int value = evaluate(node->getRValue());
	_memory[node->getLValue()] = value;
}

/// Visit a ConditionalNode and execute the 'then' statement referenced if the condition
/// is evaluated to true, otherwise execute the 'else' statement if there is one
void Interpreter::visit(ConditionalNode *node) {
	if (evaluate(node->getConditionExpression()))
		execute(node->getThenStatement());

	else if (node->getElseStatement())
		execute(node->getElseStatement());
}

/// Visit a StmtPrintNode node and print the result of the expression in the statement
void Interpreter::visit(StmtPrintNode *node) {
    int res = evaluate(node->getExpr());
    std::cout << res << std::endl;
}

/// Visit a StmtExpressionNode node and compute the expression in the statement
void Interpreter::visit(StmtExpressionNode *node) {
	evaluate(node->getExpr());
}

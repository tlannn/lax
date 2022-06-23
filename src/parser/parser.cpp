#include "parser.h"

/// Class constructor
Parser::Parser(Lexer &lex) : _lex(lex), _look(nullptr) {}

/// Parse the following source code until a complete statement is read. The statement
/// is represented by a node in the syntax tree
StmtNode* Parser::parse() {
    move();
    return program();
}

/// Read the next token in the source code
void Parser::move() {
    _look = _lex.nextToken();
}

/// Check if the type of the current token is the same as the type expected
bool Parser::check(int tokenType) {
    if (_look->getType() == tokenType) return true;
    else return false;
}

/// Check the type of the current token, and if it is the same as the type
/// expected, read the next token
void Parser::match(int tokenType) {
    if (_look->getType() == tokenType) move();
    else throw std::runtime_error("unexpected character " + std::to_string(_look->getType()) + ", got " +
                _look->toString() + " but expected " + std::to_string(tokenType) + " on line " +
                std::to_string(Lexer::line) + ":" + std::to_string(Lexer::col));
}

/// Build a node representing the program
StmtNode* Parser::program() {
	std::vector<StmtNode*> stmts;

	while (!check(TokenType::END)) {
		stmts.push_back(stmt());
	}

	return new BlockNode(stmts);
}

/// Build a node representing a sequence of statements
StmtNode* Parser::block() {
	match(TokenType::LBRACK);
	std::vector<StmtNode*> stmts;

	while (!check(TokenType::RBRACK))
		stmts.push_back(stmt());

	match(TokenType::RBRACK);

	return new BlockNode(stmts);
}

/// Build a node representing a statement
StmtNode* Parser::stmt() {
    if (check(TokenType::VAR)) {
        move();
        return varDeclStmt();
    }

    else if (check(TokenType::ID)) {
        return varAssignStmt();
    }

    else if (check(TokenType::IF)) {
        move();
        return conditionalStmt();
    }

    else if (check(TokenType::PRINT)) {
        move();
        return printStmt();
    }

    return expressionStmt();
}

/// Build a node representing a variable declaration statement
StmtNode* Parser::varDeclStmt() {
	std::string varName = _look->toString();
	move();
	match(TokenType::COLON);

	Token *type = _look;
	match(TokenType::TYPE);

	DeclNode *node;
	ExprNode *assignment = nullptr;

	if (check(TokenType::SIMEQ)) {
		move();
		assignment = logic();
	}

	if (type->toString() == Type::INT.toString())
		node = new DeclNode(varName, Type::INT, assignment);

	else if (type->toString() == Type::BOOL.toString())
		node = new DeclNode(varName, Type::BOOL, assignment);

	else throw std::runtime_error("Unknown type '" + type->toString() + "'.");

	match(TokenType::SEMICOL);

	return node;
}

/// Build a node representing a variable assignment statement
StmtNode* Parser::varAssignStmt() {
	std::string varName = _look->toString();

	move();
	match(TokenType::SIMEQ);

	AssignNode *node = new AssignNode(varName, logic());

	match(TokenType::SEMICOL);
	return node;
}

/// Build a node representing an if/else statement
StmtNode* Parser::conditionalStmt() {
    match(TokenType::LPAREN);
    ExprNode *condition = Parser::logic();
    match(TokenType::RPAREN);

    StmtNode *thenStmt = check(TokenType::LBRACK) ? block() : stmt();

    if (check(TokenType::ELSE)) {
        move();
        StmtNode *elseStmt;

        if (check(TokenType::IF)) {
            move();
            elseStmt = Parser::conditionalStmt();
        }
        else elseStmt = check(TokenType::LBRACK) ? block() : stmt();

        return new ConditionalNode(condition, thenStmt, elseStmt);
    }

    else
        return new ConditionalNode(condition, thenStmt, nullptr);
}

/// Build a node representing a print statement
StmtNode* Parser::printStmt() {
	ExprNode *expr = Parser::expr();
	match(TokenType::SEMICOL);

	return new StmtPrintNode(expr);
}

/// Build a node representing an expression statement
StmtNode* Parser::expressionStmt() {
	ExprNode *expr = Parser::expr();
	match(TokenType::SEMICOL);

	return new StmtExpressionNode(expr);
}

/// Build a node representing a logical OR expression
ExprNode* Parser::logic() {
	ExprNode *expr = join();

	while (_look->toString() == "||") {
		Token op = *_look;
		move();
		expr = new LogicalNode(expr, op, join());
	}

	return expr;
}

/// Build a node representing a logical AND expression
ExprNode* Parser::join() {
	ExprNode *expr = rel();

	while (_look->toString() == "&&") {
		Token op = *_look;
		move();
		expr = new LogicalNode(expr, op, rel());
	}

	return expr;
}

/// Build a node representing an equality or inequality expression
ExprNode* Parser::rel() {
	ExprNode *e = expr();

	while (_look->toString() == "==" || _look->toString() == "!=" || _look->toString() == "<" ||
		   _look->toString() == "<=" || _look->toString() == ">" || _look->toString() == ">=") {
		Token op = *_look;
		move();
		e = new RelationalNode(e, op, expr());
	}

	return e;
}

/// Build a node representing an expression
ExprNode* Parser::expr() {
	ExprNode *expr = term();

	while (_look->toString() == "+" || _look->toString() == "-") {
		Token op = *_look;
		move();
		expr = new BinOpNode(expr, op, term());
	}

	return expr;
}

/// Build a node representing a term
ExprNode* Parser::term() {
	ExprNode *expr = factor();

	while (_look->toString() == "*" || _look->toString() == "/") {
		Token op = *_look;
		move();
		expr = new BinOpNode(expr, op, factor());
	}

	return expr;
}

/// Build a node representing a factor
ExprNode* Parser::factor() {
	ExprNode *expr;

	switch (_look->getType()) {
		case TokenType::LPAREN: {
			move();
			expr = Parser::logic();
			match(TokenType::RPAREN);
			break;
		}
		case TokenType::NUM: {
			expr = new LiteralNode(*_look, Type::INT);
			move();
			break;
		}
		case TokenType::TRUE:
		case TokenType::FALSE: {
			expr = new LiteralNode(*_look, Type::BOOL);
			move();
			break;
		}
		case TokenType::ID: {
			expr = id();
			break;
		}
	}

	return expr;
}

/// Build a node representing an identifier
ExprNode* Parser::id() {
	Word *varName = dynamic_cast<Word*>(_look);
	move();

	return new Id(*varName);
}

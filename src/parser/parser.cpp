#include "parser.h"

/// Class constructor
Parser::Parser(Lexer lex) : _lex(lex), _previous(nullptr), _lookahead(nullptr), _errors(false) {}

/// Parse the source code until the end of file is reached. The resulting
/// program is represented by an Abstract Syntax Tree
StmtNode* Parser::parse() {
	move();
	return program();
}

/// Return whether errors occurred during parsing
bool Parser::hadErrors() const {
	return _errors;
}

/// Read the next token in the source code
Token* Parser::move() {
	_previous = _lookahead;
	_lookahead = _lex.nextToken();

	return _lookahead;
}

/// Getter for the last token read in the source code
Token* Parser::previous() {
	return _previous;
}

/// Getter for the next token to be read in the source code
Token* Parser::peek() {
	return _lookahead;
}

/// Raise an error on the next token to be read
void Parser::error(const std::string &error, ErrorMode mode) {
	this->error(error, peek(), mode);
}

/// Raise an error on a specific token
void Parser::error(const std::string &error, Token *token, ErrorMode mode) {
	_errors = true;

	switch (mode) {
		case ErrorMode::FATAL:
		case ErrorMode::PANIC:
			throw ParseError(
					Lexer::currentFile,
					token->getLine(), token->getColumn(),
					error, "SyntaxError");
		default:
			report(ParseError(
					Lexer::currentFile,
					token->getLine(), token->getColumn(),
					error, "SyntaxError")
			);
			break;
	}
}

/// Report an error to inform the user
void Parser::report(const ParseError &error) {
	Logger::error(error.what());
}

/// Return whether the end of file has been reached
bool Parser::isAtEnd() {
	return peek()->getType() == TokenType::END;
}

/// Check if the type of the current token is the same as the type expected
bool Parser::check(TokenType tokenType) {
	if (isAtEnd()) return false;
    return peek()->getType() == tokenType;
}

/// Check the type of the current token, and if it is the same as the type
/// expected, read the next token
bool Parser::match(TokenType tokenType) {
	if (check(tokenType)) {
		move();
		return true;
	}

	return false;
}

/// Read the next token in file if it matches the expected token type, or throw
/// an error if the types mismatch
void Parser::consume(TokenType type, ErrorMode mode) {
	std::string lexeme = Token::lexeme(type);
	std::string errorMessage;

	if (peek()->getType() == TokenType::END)
		errorMessage = "Expected '" + lexeme + "' before end of file";
	else if (lexeme.empty())
		errorMessage = "Unexpected token '" + peek()->toString() + "'";
	else
		errorMessage = "Expected '" + lexeme + "' before '" + peek()->toString() + "'";

	consume(type, errorMessage, mode);
}

/// Read the next token in file if it matches the expected token type, or throw
/// an error with the given error message if the types mismatch
void Parser::consume(TokenType type, const std::string &errorMessage, ErrorMode mode) {
	if (check(type)) move();

	else error(errorMessage, mode);
}

/// Synchronize the parser when an error occurred and move until a delimiter
/// token - a semicolon or a keyword
void Parser::synchronize() {
	while (!isAtEnd()) {
		if (previous()->getType() == TokenType::SEMICOL) return;

		switch (peek()->getType()) {
			case TokenType::IF:
			case TokenType::ELSE:
			case TokenType::VAR:
			case TokenType::TYPE:
			case TokenType::ID:
			case TokenType::PRINT:
				return;
		}

		move();
	}
}

/// Build a node representing the program
StmtNode* Parser::program() {
	std::vector<StmtNode*> stmts;

	while (!isAtEnd())
		stmts.push_back(stmt());

	return new SeqNode(stmts);
}

/// Build a node representing a block of statements
StmtNode* Parser::block() {
	consume(TokenType::LBRACE, ErrorMode::REPAIR);
	std::vector<StmtNode*> stmts;

	while (!check(TokenType::RBRACE) && !isAtEnd())
		stmts.push_back(stmt());

	consume(TokenType::RBRACE, ErrorMode::REPAIR);

	return new BlockNode(new SeqNode(stmts));
}

/// Build a node representing a statement
StmtNode* Parser::stmt() {
	try {
		if (match(TokenType::VAR) || match(TokenType::TYPE)) return declaration();
		else if (match(TokenType::ID)) return varAssignStmt();
		else if (match(TokenType::IF)) return conditionalStmt();
		else if (match(TokenType::INCLUDE)) return includeStmt();
		else if (match(TokenType::PRINT)) return printStmt();
		else return expressionStmt();
	}

	// Catch LexErrors and ParseErrors
	catch (std::exception &e) {
		Logger::error(e.what());
		synchronize();
		return nullptr;
	}
}

/// Build a node representing an include statement
StmtNode* Parser::includeStmt() {
	consume(TokenType::STRING, "Expected string");
	std::string filename = previous()->toString();

	consume(TokenType::SEMICOL);

	// Open the new file with the lexer
	_lex.pushFile(filename);
	move(); // Read the first token

	// Parse the new file
	StmtNode* include = program();

	// Recover the previous file state
	_lex.popFile();
	move(); // Read the next token

	return include;
}

/// Build a node representing a variable declaration statement
StmtNode* Parser::declaration() {
	// Determine the variable type based on the keyword
	Type *type = previous()->getType() == TokenType::VAR ? &Type::NONE : Type::getType(previous());
	move();
	Token *identifier = previous();

	ExprNode *assignment = match(TokenType::SIMEQ) ? expr() : nullptr;

	consume(TokenType::SEMICOL);

	return new DeclNode(identifier, *type, assignment);
}

/// Build a node representing a variable assignment statement
StmtNode* Parser::varAssignStmt() {
	Token *identifier = previous();

	consume(TokenType::SIMEQ);

	auto *node = new AssignNode(identifier, expr());

	consume(TokenType::SEMICOL);

	return node;
}

/// Build a node representing an if/else statement
StmtNode* Parser::conditionalStmt() {
    consume(TokenType::LPAREN, ErrorMode::REPAIR);
    ExprNode *condition = Parser::expr();
    consume(TokenType::RPAREN, ErrorMode::REPAIR);

    StmtNode *thenStmt = check(TokenType::LBRACE) ? block() : stmt();

    if (match(TokenType::ELSE)) {
        StmtNode *elseStmt;

        if (match(TokenType::IF))
            elseStmt = Parser::conditionalStmt();

        else elseStmt = check(TokenType::LBRACE) ? block() : stmt();

        return new ConditionalNode(condition, thenStmt, elseStmt);
    }

    else
        return new ConditionalNode(condition, thenStmt, nullptr);
}

/// Build a node representing a print statement
StmtNode* Parser::printStmt() {
	ExprNode *expr = Parser::expr();
	consume(TokenType::SEMICOL);

	return new StmtPrintNode(expr);
}

/// Build a node representing an expression statement
StmtNode* Parser::expressionStmt() {
	ExprNode *expr = Parser::expr();
	consume(TokenType::SEMICOL);

	return new StmtExpressionNode(expr);
}

/// Build a node representing an expression
ExprNode* Parser::expr() {
	return logic();
}

/// Build a node representing a logical OR expression
ExprNode* Parser::logic() {
	ExprNode *expr = join();

	while (match(TokenType::OR)) {
		Token *op = previous();
		expr = new LogicalNode(expr, op, join());
	}

	return expr;
}

/// Build a node representing a logical AND expression
ExprNode* Parser::join() {
	ExprNode *expr = rel();

	while (match(TokenType::AND)) {
		Token *op = previous();
		expr = new LogicalNode(expr, op, rel());
	}

	return expr;
}

/// Build a node representing an equality or inequality expression
ExprNode* Parser::rel() {
	ExprNode *expr = binop();

	while (match(TokenType::EQ) || match(TokenType::NEQ) ||
			match(TokenType::SL) || match(TokenType::LE) ||
			match(TokenType::SG) || match(TokenType::GE)) {
		Token *op = previous();
		expr = new RelationalNode(expr, op, binop());
	}

	return expr;
}

/// Build a node representing a binary operation
ExprNode* Parser::binop() {
	ExprNode *expr = term();

	while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
		Token *op = previous();
		expr = new BinOpNode(expr, op, term());
	}

	return expr;
}

/// Build a node representing a term
ExprNode* Parser::term() {
	ExprNode *expr = factor();

	while (match(TokenType::STAR) || match(TokenType::SLASH)) {
		Token *op = previous();
		expr = new BinOpNode(expr, op, factor());
	}

	return expr;
}

/// Build a node representing a factor
ExprNode* Parser::factor() {
	ExprNode *expr = nullptr;

	// Read the next token
	move();

	// Create node depending on the type of the token read
	switch (previous()->getType()) {
		case TokenType::LPAREN: {
			expr = Parser::logic();
			match(TokenType::RPAREN);
			break;
		}
		case TokenType::NUM: {
			expr = new LiteralNode(previous(), Type::INT);
			break;
		}
		case TokenType::STRING:
			expr = new LiteralNode(previous(), Type::STRING);
			break;
		case TokenType::TRUE:
		case TokenType::FALSE: {
			expr = new LiteralNode(previous(), Type::BOOL);
			break;
		}
		case TokenType::ID: {
			expr = new Id(previous());
			break;
		}
		case TokenType::SEMICOL:
			error("Expected expression before '" + previous()->toString() + "'", previous());
			break;
		default:
			error("Unexpected token '" + previous()->toString() + "'", previous());
			break;
	}

	return expr;
}

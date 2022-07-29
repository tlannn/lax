#include "parser.h"

/// Class constructor
Parser::Parser(Lexer &lex) : _lex(lex), _previous(nullptr), _lookahead(nullptr), _errors(false) {}

/// Parse the source code until the end of file is reached. The resulting
/// program is represented by an Abstract Syntax Tree
std::unique_ptr<ASTNode> Parser::parse() {
	move();
	return program();
}

/// Return whether errors occurred during parsing
bool Parser::hadErrors() const {
	return _errors;
}

/// Read the next token in the source code
Token* Parser::move() {
	_previous = std::move(_lookahead);
	_lookahead = _lex.nextToken();

	return _lookahead.get();
}

/// Getter for the last token read in the source code
Token* Parser::previous() {
	return _previous.get();
}

/// Getter for the next token to be read in the source code
Token* Parser::peek() {
	return _lookahead.get();
}

/// Raise an error on the next token to be read
void Parser::error(const std::string &error, ErrorMode mode) {
	this->error(error, peek(), mode);
}

/// Raise an error on a specific token
void Parser::error(const std::string &error, Token* token, ErrorMode mode) {
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
std::unique_ptr<StmtNode> Parser::program() {
	std::vector<std::unique_ptr<StmtNode>> stmts;

	while (!isAtEnd())
		stmts.push_back(stmt());

	return std::make_unique<SeqNode>(std::move(stmts));
}

/// Build a node representing a block of statements
std::unique_ptr<BlockNode> Parser::block() {
	consume(TokenType::LBRACE, ErrorMode::REPAIR);
	std::vector<std::unique_ptr<StmtNode>> stmts;

	while (!check(TokenType::RBRACE) && !isAtEnd())
		stmts.push_back(stmt());

	consume(TokenType::RBRACE, ErrorMode::REPAIR);

	return std::make_unique<BlockNode>(std::make_unique<SeqNode>(std::move(stmts)));
}

/// Build a node representing a statement
std::unique_ptr<StmtNode> Parser::stmt() {
	try {
		if (match(TokenType::VAR) || match(TokenType::TYPE)) return declaration();
//		else if (match(TokenType::ID)) return varAssignStmt();
		else if (match(TokenType::FUN)) return function();
		else if (match(TokenType::RETURN)) return returnStmt();
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
std::unique_ptr<StmtNode> Parser::includeStmt() {
	consume(TokenType::STRING, "Expected string");
	std::string filename = previous()->toString();

	consume(TokenType::SEMICOL);

	// Open the new file with the lexer
	_lex.pushFile(filename);
	move(); // Read the first token

	// Parse the new file
	std::unique_ptr<StmtNode> include = program();

	// Recover the previous file state
	_lex.popFile();
	move(); // Read the next token

	return include;
}

/// Build a node representing a variable declaration statement
std::unique_ptr<DeclNode> Parser::declaration() {
	// Determine the variable type based on the keyword
	ValueType type = previous()->getType() == TokenType::VAR ? ValueType::VAL_NULL : ValueType::getType(previous());
	move();
	std::shared_ptr<Token> identifier = std::move(_previous);

	std::unique_ptr<ExprNode> assignment = match(TokenType::SIMEQ) ? expr() : nullptr;

	consume(TokenType::SEMICOL);

	return std::make_unique<DeclNode>(identifier, type, std::move(assignment));
}

/// Build a node representing a variable assignment statement
std::unique_ptr<ExprNode> Parser::varAssignStmt() {
	/*if (match(TokenType::ID)) {
		consume(TokenType::ID);

		consume(TokenType::SIMEQ);

		auto node = std::make_unique<AssignNode>(std::move(_previous), expr());

		consume(TokenType::SEMICOL);

		return node;
	}

	return logic();*/


	std::unique_ptr<ExprNode> node = logic();

	if (match(TokenType::SIMEQ)) {
		std::unique_ptr<Token> equals = std::move(_previous);
		std::unique_ptr<ExprNode> value = varAssignStmt();

		if (Id *id = dynamic_cast<Id*>(node.get())) {
			return std::make_unique<AssignNode>(std::move(node), std::move(value));
		}
	}

//	consume(TokenType::SEMICOL);

	return node;
}

/// Build a node representing a function declaration statement
std::unique_ptr<FunNode> Parser::function() {
	// Read the function identifier
	consume(TokenType::ID);
	auto name = std::move(_previous);

	consume(TokenType::LPAREN);

	std::vector<std::unique_ptr<Variable>> params;
	// Check if parameters are present
	if (!check(TokenType::RPAREN)) {
		do {
			// Read parameter type
			consume(TokenType::TYPE);
			auto type = ValueType::getType(previous());

			// Read parameter name
			consume(TokenType::ID);
			auto identifier = std::move(_previous);

			auto variable = std::make_unique<Variable>(std::move(identifier), type);
			params.push_back(std::move(variable));
		} while (match(TokenType::COMMA));
	}

	// Read the parameters closing parenthesis
	consume(TokenType::RPAREN);

	// The function returns nothing by default
	ValueType returnType = ValueType::VAL_NULL;

	// Search for the function return type
	if (match(TokenType::COLON)) {
		consume(TokenType::TYPE);
		returnType = ValueType::getType(previous());
	}

	// Raise an error if no function body is found
	if (!check(TokenType::LBRACE))
		error("Expected function body", peek());

	// Read the function body
	std::unique_ptr<BlockNode> body = block();

	return std::make_unique<FunNode>(std::move(name), returnType, std::move(params), std::move(body));
}

/// Build a node representing a return statement
std::unique_ptr<ReturnNode> Parser::returnStmt() {
	auto token = std::move(_previous);
	std::unique_ptr<ExprNode> value;

	if (!check(TokenType::SEMICOL))
		value = expr();

	consume(TokenType::SEMICOL);
	return std::make_unique<ReturnNode>(std::move(token), std::move(value));
}

/// Build a node representing an if/else statement
std::unique_ptr<ConditionalNode> Parser::conditionalStmt() {
    consume(TokenType::LPAREN, ErrorMode::REPAIR);
    std::unique_ptr<ExprNode> condition = Parser::expr();
    consume(TokenType::RPAREN, ErrorMode::REPAIR);

    std::unique_ptr<StmtNode> thenStmt = check(TokenType::LBRACE) ? block() : stmt();

    if (match(TokenType::ELSE)) {
        std::unique_ptr<StmtNode> elseStmt;

        if (match(TokenType::IF))
            elseStmt = Parser::conditionalStmt();

        else elseStmt = check(TokenType::LBRACE) ? block() : stmt();

        return std::make_unique<ConditionalNode>(std::move(condition), std::move(thenStmt), std::move(elseStmt));
    }

    else
        return std::make_unique<ConditionalNode>(std::move(condition), std::move(thenStmt), nullptr);
}

/// Build a node representing a print statement
std::unique_ptr<StmtPrintNode> Parser::printStmt() {
	std::unique_ptr<ExprNode> expr = Parser::expr();
	consume(TokenType::SEMICOL);

	return std::make_unique<StmtPrintNode>(std::move(expr));
}

/// Build a node representing an expression statement
std::unique_ptr<StmtExpressionNode> Parser::expressionStmt() {
	std::unique_ptr<ExprNode> expr = Parser::expr();
	consume(TokenType::SEMICOL);

	return std::make_unique<StmtExpressionNode>(std::move(expr));
}

/// Build a node representing an expression
std::unique_ptr<ExprNode> Parser::expr() {
	return varAssignStmt();
}

/// Build a node representing a logical OR expression
std::unique_ptr<ExprNode> Parser::logic() {
	std::unique_ptr<ExprNode> expr = join();

	while (match(TokenType::OR)) {
		std::unique_ptr<Token> op = std::move(_previous);
		expr = std::make_unique<LogicalNode>(std::move(expr), std::move(op), join());
	}

	return expr;
}

/// Build a node representing a logical AND expression
std::unique_ptr<ExprNode> Parser::join() {
	std::unique_ptr<ExprNode> expr = rel();

	while (match(TokenType::AND)) {
		std::unique_ptr<Token> op = std::move(_previous);
		expr = std::make_unique<LogicalNode>(std::move(expr), std::move(op), rel());
	}

	return expr;
}

/// Build a node representing an equality or inequality expression
std::unique_ptr<ExprNode> Parser::rel() {
	std::unique_ptr<ExprNode> expr = binop();

	while (match(TokenType::EQ) || match(TokenType::NEQ) ||
			match(TokenType::SL) || match(TokenType::LE) ||
			match(TokenType::SG) || match(TokenType::GE)) {
		std::unique_ptr<Token> op = std::move(_previous);
		expr = std::make_unique<RelationalNode>(std::move(expr), std::move(op), binop());
	}

	return expr;
}

/// Build a node representing a binary operation
std::unique_ptr<ExprNode> Parser::binop() {
	std::unique_ptr<ExprNode> expr = term();

	while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
		std::unique_ptr<Token> op = std::move(_previous);
		expr = std::make_unique<BinOpNode>(std::move(expr), std::move(op), term());
	}

	return expr;
}

/// Build a node representing a term
std::unique_ptr<ExprNode> Parser::term() {
	std::unique_ptr<ExprNode> expr = unary();

	while (match(TokenType::STAR) || match(TokenType::SLASH)) {
		std::unique_ptr<Token> op = std::move(_previous);
		expr = std::make_unique<BinOpNode>(std::move(expr), std::move(op), unary());
	}

	return expr;
}

/// Build a node representing an unary
std::unique_ptr<ExprNode> Parser::unary() {
	if (match(TokenType::PLUS) || match(TokenType::MINUS) || match(TokenType::BANG)) {
		std::unique_ptr<Token> op = std::move(_previous);
		return std::make_unique<UnaryNode>(std::move(op), unary());
	}

	return call();
}

std::unique_ptr<ExprNode> Parser::call() {
	std::unique_ptr<ExprNode> expr = factor();

	// While in a function call chain
	while (match(TokenType::LPAREN)) {
		expr = arguments(std::move(expr));
	}

	return expr;
}

/// Build a node representing a factor
std::unique_ptr<ExprNode> Parser::factor() {
	std::unique_ptr<ExprNode> expr = nullptr;

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
			Value value = INT_VAL(std::stoi(_previous->toString()));

			expr = std::make_unique<LiteralNode>(std::move(_previous), value);

//			expr = std::make_unique<LiteralNode>(std::move(_previous), ValueType::VAL_INT);
			break;
		}
		case TokenType::STRING: {
			Value value = OBJ_VAL(new ObjString(_previous->toString()));

			expr = std::make_unique<LiteralNode>(std::move(_previous), value);
			//			expr = std::make_unique<LiteralNode>(std::move(_previous), ValueType::STRING);
			break;
		}
		case TokenType::TRUE:
		case TokenType::FALSE: {
			Value value = BOOL_VAL(previous()->getType() == TokenType::TRUE);

			expr = std::make_unique<LiteralNode>(std::move(_previous), value);
//			expr = std::make_unique<LiteralNode>(std::move(_previous), ValueType::VAL_BOOL);
			break;
		}
		case TokenType::ID: {
			expr = std::make_unique<Id>(std::move(_previous));
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

std::unique_ptr<ExprNode> Parser::arguments(std::unique_ptr<ExprNode> callee) {
	std::vector<std::unique_ptr<ExprNode>> args;

	if (!check(TokenType::RPAREN)) {
		do {
			if (args.size() >= 255)
				error("Arguments count can't exceed 255", peek());

			args.push_back(expr());
		} while (match(TokenType::COMMA));
	}

	consume(TokenType::RPAREN, ErrorMode::NON_PANIC);

	return std::make_unique<CallNode>(std::move(callee), std::move(_previous), std::move(args));
}

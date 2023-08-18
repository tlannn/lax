#include "parser/Parser.h"
#include "ast/AST.h"
#include "ast/ASTIncludes.h"
#include "lexer/Lexer.h"
#include "objects/ObjString.h"
#include "objects/Variable.h"
#include "parser/ParseError.h"
#include "symbols/SymbolTable.h"
#include "utils/Logger.h"
#include "values/PrimitiveType.h"

/// Class constructor
Parser::Parser(Lexer& lex) :
    m_lex(lex),
    m_previous(nullptr),
    m_lookahead(nullptr),
    m_errors(false) {}

/// Parse the source code until the end of file is reached. The resulting
/// program is represented by an Abstract Syntax Tree
std::unique_ptr<AST> Parser::parse() {
    move();
    return std::make_unique<AST>(std::move(program()));
}

/// Return whether errors occurred during parsing
bool Parser::hadErrors() const {
    return m_errors;
}

/// Read the next token in the source code
Token* Parser::move() {
    m_previous = std::move(m_lookahead);
    m_lookahead = m_lex.nextToken();

    return m_lookahead.get();
}

/// Getter for the last token read in the source code
Token* Parser::previous() {
    return m_previous.get();
}

/// Getter for the next token to be read in the source code
Token* Parser::peek() {
    return m_lookahead.get();
}

/// Raise an error on the next token to be read
void Parser::error(const std::string& error, ErrorMode mode) {
    this->error(error, peek(), mode);
}

/// Raise an error on a specific token
void Parser::error(const std::string& error, Token* token, ErrorMode mode) {
    m_errors = true;

    switch (mode) {
        case ErrorMode::FATAL:
        case ErrorMode::PANIC:
            throw ParseError(
                Lexer::currentFile,
                token->getLine(), token->getColumn(),
                error, "SyntaxError"
            );
        default:
            report(
                ParseError(
                    Lexer::currentFile,
                    token->getLine(), token->getColumn(),
                    error, "SyntaxError"
                )
            );
            break;
    }
}

/// Report an error to inform the user
void Parser::report(const ParseError& error) {
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
        errorMessage = "Expected '" + lexeme + "' before '" +
            peek()->toString()+ "'";

    consume(type, errorMessage, mode);
}

/// Read the next token in file if it matches the expected token type, or throw
/// an error with the given error message if the types mismatch
void Parser::consume(TokenType type, const std::string& errorMessage,
    ErrorMode mode)
{
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
            case TokenType::ID: return;
            default: break;
        }

        move();
    }
}

ObjString* Parser::identifier(const std::string& name) {
    return ObjString::copyString(name);
}

/// Build a node representing the program
UStmtNode Parser::program() {
    std::vector<UStmtNode> stmts;

    while (!isAtEnd())
        stmts.push_back(stmt());

    return std::make_unique<SeqNode>(std::move(stmts));
}

/// Build a node representing a block of statements
UBlockNode Parser::block() {
    consume(TokenType::LBRACE, ErrorMode::REPAIR);
    std::vector<UStmtNode> stmts;

    while (!check(TokenType::RBRACE) && !isAtEnd())
        stmts.push_back(stmt());

    consume(TokenType::RBRACE, ErrorMode::REPAIR);

    return std::make_unique<BlockNode>(
        std::make_unique<SeqNode>(std::move(stmts))
    );
}

/// Build a node representing a scoped block of statements
UBlockNode Parser::scopedBlock() {
    auto block = this->block();

    return std::move(block);
}

/// Build a node representing a statement
UStmtNode Parser::stmt() {
    try {
        if (match(TokenType::VAR) || match(TokenType::TYPE))
            return declaration();
        else if (match(TokenType::FUN))
            return function();
        else if (match(TokenType::RETURN))
            return returnStmt();
        else if (match(TokenType::IF))
            return conditionalStmt();
        else if (match(TokenType::INCLUDE))
            return includeStmt();
        else if (check(TokenType::LBRACE))
            return scopedBlock();

        return expressionStmt();
    }

    // Catch LexErrors and ParseErrors
    catch (std::exception& e) {
        Logger::error(e.what());
        synchronize();
        return nullptr;
    }
}

/// Build a node representing an include statement
UStmtNode Parser::includeStmt() {
    consume(TokenType::STR, "Expected string");
    std::string filename = previous()->toString();

    consume(TokenType::SEMICOL);

    // Open the new file with the lexer
    m_lex.pushFile(filename);
    move(); // Read the first token

    // Parse the new file
    UStmtNode include = program();

    // Recover the previous file state
    m_lex.popFile();
    move(); // Read the next token

    return include;
}

/// Build a node representing a variable declaration statement
UDeclNode Parser::declaration() {
    // Determine the variable type based on the keyword
    LaxType* type = nullptr;
    if (previous()->getType() != TokenType::VAR)
        type = PrimitiveType::getType(previous());

    move();
    ObjString* name = identifier(m_previous->toString());
    auto token = std::move(m_previous);

    UExprNode assignment = match(TokenType::SIMEQ) ? expr() : nullptr;

    consume(TokenType::SEMICOL);

    auto node = std::make_unique<DeclNode>(
        std::move(token), name, type, std::move(assignment)
    );
    node->setScope(&SymbolTable::instance()->currentScope());
    return std::move(node);
}

/// Build a node representing a variable assignment statement
UExprNode Parser::varAssignStmt() {
    UExprNode node = logic();

    if (match(TokenType::SIMEQ)) {
        UToken equals = std::move(m_previous);
        UExprNode value = varAssignStmt();

        if (auto* id = dynamic_cast<IdNode*>(node.get())) {
            return std::make_unique<AssignNode>(
                id->getName(), std::move(equals), std::move(value)
            );
        }
    }

    return node;
}

/// Build a node representing a function declaration statement
UFunNode Parser::function() {
    // Read the function identifier
    consume(TokenType::ID);
    ObjString* name = identifier(m_previous->toString());
    auto token = std::move(m_previous);

    consume(TokenType::LPAREN);

    std::vector<std::unique_ptr<Variable>> params;
    // Check if parameters are present
    if (!check(TokenType::RPAREN)) {
        do {
            // Read parameter type
            consume(TokenType::TYPE);
            LaxType* type = PrimitiveType::getType(previous());

            // Read parameter name
            consume(TokenType::ID);
            auto identifier = std::move(m_previous);

            auto variable = std::make_unique<Variable>(
                std::move(identifier), type
            );
            params.push_back(std::move(variable));
        } while (match(TokenType::COMMA));
    }

    // Read the parameters closing parenthesis
    consume(TokenType::RPAREN);

    // The function returns nothing by default
    LaxType* returnType = &PrimitiveType::VOID;

    // Search for the function return type
    if (match(TokenType::COLON)) {
        consume(TokenType::TYPE);
        returnType = PrimitiveType::getType(previous());
    }

    // Raise an error if no function body is found
    if (!check(TokenType::LBRACE))
        error("Expected function body", peek());

    // Read the function body
    UBlockNode body = block();

    return std::make_unique<FunNode>(
        std::move(token), name, returnType, std::move(params), std::move(body)
    );
}

/// Build a node representing a return statement
UReturnNode Parser::returnStmt() {
    auto token = std::move(m_previous);
    UExprNode value;

    if (!check(TokenType::SEMICOL))
        value = expr();

    consume(TokenType::SEMICOL);
    return std::make_unique<ReturnNode>(std::move(token), std::move(value));
}

/// Build a node representing an if/else statement
UConditionalNode Parser::conditionalStmt() {
    consume(TokenType::LPAREN, ErrorMode::REPAIR);
    UExprNode condition = Parser::expr();
    consume(TokenType::RPAREN, ErrorMode::REPAIR);

    UStmtNode thenStmt = check(TokenType::LBRACE) ? block() : stmt();

    if (match(TokenType::ELSE)) {
        UStmtNode elseStmt;

        if (match(TokenType::IF))
            elseStmt = Parser::conditionalStmt();

        else
            elseStmt = check(TokenType::LBRACE) ? block() : stmt();

        return std::make_unique<ConditionalNode>(
            std::move(condition), std::move(thenStmt), std::move(elseStmt)
        );
    }

    return std::make_unique<ConditionalNode>(
        std::move(condition), std::move(thenStmt), nullptr
    );
}

/// Build a node representing an expression statement
UStmtExpressionNode Parser::expressionStmt() {
    UExprNode expr = Parser::expr();
    consume(TokenType::SEMICOL);

    return std::make_unique<StmtExpressionNode>(std::move(expr));
}

/// Build a node representing an expression
UExprNode Parser::expr() {
    return varAssignStmt();
}

/// Build a node representing a logical OR expression
UExprNode Parser::logic() {
    UExprNode expr = join();

    while (match(TokenType::OR)) {
        UToken op = std::move(m_previous);
        expr = std::make_unique<LogicalNode>(
            std::move(expr), std::move(op), join()
        );
    }

    return expr;
}

/// Build a node representing a logical AND expression
UExprNode Parser::join() {
    UExprNode expr = rel();

    while (match(TokenType::AND)) {
        UToken op = std::move(m_previous);
        expr = std::make_unique<LogicalNode>(
            std::move(expr), std::move(op), rel()
        );
    }

    return expr;
}

/// Build a node representing an equality or inequality expression
UExprNode Parser::rel() {
    UExprNode expr = binop();

    while (match(TokenType::EQ) || match(TokenType::NEQ) ||
           match(TokenType::SL) || match(TokenType::LE) ||
           match(TokenType::SG) || match(TokenType::GE))
    {
        UToken op = std::move(m_previous);
        expr = std::make_unique<RelationalNode>(
            std::move(expr), std::move(op), binop()
        );
    }

    return expr;
}

/// Build a node representing a binary operation
UExprNode Parser::binop() {
    UExprNode expr = term();

    while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
        UToken op = std::move(m_previous);
        expr = std::make_unique<BinOpNode>(
            std::move(expr), std::move(op), term()
        );
    }

    return expr;
}

/// Build a node representing a term
UExprNode Parser::term() {
    UExprNode expr = unary();

    while (match(TokenType::STAR) || match(TokenType::SLASH)) {
        UToken op = std::move(m_previous);
        expr = std::make_unique<BinOpNode>(
            std::move(expr), std::move(op), unary()
        );
    }

    return expr;
}

/// Build a node representing an unary
UExprNode Parser::unary() {
    if (match(TokenType::PLUS) ||
        match(TokenType::MINUS) ||
        match(TokenType::BANG))
    {
        UToken op = std::move(m_previous);
        return std::make_unique<UnaryNode>(std::move(op), unary());
    }

    return call();
}

UExprNode Parser::call() {
    UExprNode expr = factor();

    // While in a function call chain
    while (match(TokenType::LPAREN))
        expr = arguments(std::move(expr));

    return expr;
}

/// Build a node representing a factor
UExprNode Parser::factor() {
    UExprNode expr = nullptr;

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
            Value value = Value::integer(std::stoi(m_previous->toString()));

            expr = std::make_unique<LiteralNode>(std::move(m_previous), value);
            break;
        }
        case TokenType::STR: {
            ObjString* string = ObjString::copyString(m_previous->toString());

            expr = std::make_unique<LiteralNode>(
                std::move(m_previous), Value::object(string)
            );
            break;
        }
        case TokenType::TRUE:
        case TokenType::FALSE: {
            Value value = Value::boolean(
                previous()->getType() == TokenType::TRUE
            );

            expr = std::make_unique<LiteralNode>(std::move(m_previous), value);
            break;
        }
        case TokenType::ID: {
            expr = std::make_unique<IdNode>(std::move(m_previous));
            break;
        }
        case TokenType::SEMICOL:
            error("Expected expression before '" + previous()->toString() + "'",
                  previous());
            break;
        default:
            error("Unexpected token '" + previous()->toString() + "'",
                  previous());
            break;
    }

    return expr;
}

UExprNode Parser::arguments(UExprNode callee) {
    std::vector<UExprNode> args;
    UToken paren = std::move(m_previous);

    if (!check(TokenType::RPAREN)) {
        do {
            if (args.size() >= 255)
                error("Arguments count can't exceed 255", peek());

            args.push_back(expr());
        } while (match(TokenType::COMMA));
    }

    consume(TokenType::RPAREN, ErrorMode::NON_PANIC);

    return std::make_unique<CallNode>(
        std::move(callee),
        std::move(paren),
        std::move(args)
    );
}

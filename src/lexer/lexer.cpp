#include <iostream>
#include "lexer.h"

std::string Lexer::currentFile;

/// Class constructor
Lexer::Lexer(const std::string &filename) : _source(std::make_unique<std::ifstream>()),
	_startIndex(-1), _index(-1), _line(1), _col(0), _startLine(1), _startCol(0) {
	// Reserve types
	reserve("int", TokenType::TYPE);
	reserve("bool", TokenType::TYPE);
	reserve("string", TokenType::TYPE);

	// Reserve keywords
	reserve("true", TokenType::TRUE);
	reserve("false", TokenType::FALSE);
	reserve("if", TokenType::IF);
	reserve("else", TokenType::ELSE);
	reserve("var", TokenType::VAR);
	reserve("print", TokenType::PRINT);
	reserve("include", TokenType::INCLUDE);

	openFile(filename);
}

/// Return the part containing the path to a file
std::string Lexer::getPath(const std::string &filepath) {
	size_t index = filepath.find_last_of('/');
	return filepath.substr(0, index + 1);
}

/// Open a stream to read a file and place the cursor at the beginning
void Lexer::openFile(const std::string &filename) {
	std::string filepath;

	// Determine the path to the file according to the paths to previous files opened
	if (!_mementos.empty()) {
		Memento *memento = &_mementos.top();

		while (memento) {
			filepath.insert(0, getPath(memento->getSource()));
			memento = memento->getPrevious();
		}
	}

	// Close the old stream and open a new one to the file
	_source->close();
	_source->open(filepath + filename);

	if (!_source->is_open())
		error("Could not open file '" + filename + "'");

	Lexer::currentFile = filename;

	// Reset all attributes
	_startLine = 1;
	_startCol = 0;
	_line = 1;
	_col = 0;
	_index = -1;
}

/// Open a file and push it on top of the stack of files opened
void Lexer::pushFile(const std::string &filename) {
	_mementos.push(
			Memento(!_mementos.empty() ? &_mementos.top() : nullptr,
						   Lexer::currentFile, _startIndex, _startLine, _startCol
					   )
	);

	openFile(filename);
}

/// Pop the last file opened and restore the state of the previous file
void Lexer::popFile() {
	Memento memento = _mementos.top();
	openFile(memento.getSource());
	_source->seekg(memento.getIndex()); // Move cursor to old position in file, before the last token read

	_line = memento.getLine();
	_col = memento.getCol();
	_index = memento.getIndex();

	// Delete the old memento
	_mementos.pop();
	/*Memento *memento = _memento;
	delete memento;*/
}

/// Continue the reading of the source code and return the next token analyzed
std::unique_ptr<Token> Lexer::nextToken() {
	int c = advance();

	// Set the start position of the next token to the cursor current position
	_startIndex = _index;
	_startCol = _col;
	_startLine = _line;

    // Skip whitespaces, tabulations and newlines
    for (;; c = advance()) {
        if (c == ' ' || c == '\t') { _startCol = _col + 1; _startIndex = _index + 1; } // Anticipate advance()
        else if (c == '\n') { ++_line; _col = 0; } // Place cursor to the beginning of next line
        else break;
    }

    // Recognize other tokens
    switch (c) {
		case EOF: return createToken(TokenType::END);
		case '(': return createToken(TokenType::LPAREN);
		case ')': return createToken(TokenType::RPAREN);
		case '[': return createToken(TokenType::LBRACK);
		case ']': return createToken(TokenType::RBRACK);
		case '{': return createToken(TokenType::LBRACE);
		case '}': return createToken(TokenType::RBRACE);
		case ':': return createToken(TokenType::COLON);
		case ';': return createToken(TokenType::SEMICOL);
		case '+': return createToken(TokenType::PLUS);
		case '-': return createToken(TokenType::MINUS);
		case '*': return createToken(TokenType::STAR);
		case '/':
			if (match('/')) { inlineComment(); return nextToken(); }
			else if (peek() == '*') { blockComment(); return nextToken(); }
			else return createToken(TokenType::SLASH);
        case '&': if (match('&')) return createToken(TokenType::AND); break;
        case '|': if (match('|')) return createToken(TokenType::OR); break;
		case '!': return createToken(match('=') ? TokenType::NEQ : TokenType::BANG);
		case '=': return createToken(match('=') ? TokenType::EQ : TokenType::SIMEQ);
        case '<': return createToken(match('=') ? TokenType::LE : TokenType::SL);
        case '>': return createToken(match('=') ? TokenType::GE : TokenType::SG);
		case '"': return string();
		default:
			if (isDigit(c)) return number(c); // Recognize numbers
			else if (isAlpha(c)) return identifier(c); // Recognize words
			return createToken(TokenType::UNKNOWN, std::string(1, static_cast<char>(c)));
    }

	return createToken(TokenType::UNKNOWN, std::string(1, static_cast<char>(c)));
}

/// Reserve a word, meaning it cannot be used as an identifier (for variables,
/// functions, classes, etc.)
void Lexer::reserve(const std::string &word, TokenType type) {
    _words[word] = type;
}

/// Create a token of a specific type. The lexeme is deduced from the token type
std::unique_ptr<Token> Lexer::createToken(TokenType type) {
	return createToken(type, Token::lexeme(type));
}

/// Create a token of specific type and lexeme
std::unique_ptr<Token> Lexer::createToken(TokenType type, const std::string &lexeme) const {
	return std::make_unique<Token>(lexeme, type, _startLine, _startCol);
}

/// Throw an error
void Lexer::error(const std::string &message) const {
	throw LexError(Lexer::currentFile, _startLine, _startCol, message, "LexerError");
}

/// Return whether the cursor is at the end of the current file
bool Lexer::isAtEnd() {
	return _source->peek() == EOF;
}

/// Read a character in the source code and return it
int Lexer::advance() {
	++_index;
	++_col;
	return _source->get();
}

/// Check if the next character in the source code is the expected one, and
/// if it is the case, consume it
bool Lexer::match(char expected) {
	if (isAtEnd() || peek() != expected) return false;
	advance();
    return true;
}

/// Look at the next character in the source code, but does not move the cursor
int Lexer::peek() {
	return _source->peek();
}

/// Read a string in the source code
std::unique_ptr<Token> Lexer::string() {
	std::string buffer;
	int c;

	// Read in buffer all characters until closing quotation, end of file or end of line
	while (peek() != '"' && peek() != '\n' && !isAtEnd()) {
		c = advance();
		buffer += static_cast<char>(c);
	}

	// Throw error if end of line or file is reached before a closing quote is met
	if (isAtEnd())
		error("End of file reached before string end");
	else if (peek() == '\n')
		error("Unterminated string literal");

	advance(); // Skip the closing quotation

	return createToken(TokenType::STRING, buffer);
}

/// Read a number in the source code
std::unique_ptr<Token> Lexer::number(int d) {
	int n = d - '0';

	while (isDigit(peek())) {
		d = advance();
		n = 10 * n + d - '0';
	}

	return createToken(TokenType::NUM, std::to_string(n));
}

/// Read an identifier in the source code
std::unique_ptr<Token> Lexer::identifier(int c) {
	// Read in a buffer all following letters
	std::string buffer;
	buffer += static_cast<char>(c);

	while (isAlphaNum(peek())) {
		c = advance();
		buffer += static_cast<char>(c);
	}

	// Search for the word in reserved keywords
	auto it = _words.find(buffer);

	// If the word is already reserved, return it
	if (_words.find(buffer) != _words.end())
		return createToken(it->second, it->first);

	else {
		// Reserve this word as an identifier
		_words[buffer] = TokenType::ID;
		return createToken(TokenType::ID, buffer);
	}
}

/// Skip an inline comment
void Lexer::inlineComment() {
	while (peek() != '\n' && !isAtEnd()) advance();
}

/// Skip a block comment, with nested block comments
void Lexer::blockComment() {
	short int count = 0;

	std::stack<short int> s;
	while (match('*')) ++count;
	s.push(count);
	count = 0;

	while (!s.empty() && !isAtEnd()) {
		// Check for opening comments
		if (match('/') && peek() == '*') {
			// Count the number of stars and push into the stack
			while (match('*')) ++count;
			s.push(count);

			count = 0; // Reset counter
		}

		// Check for closing comments
		else if (peek() == '*') {
			while (match('*')) ++count;

			// Pop from the stack if the number of stars is the same as the last tag in stack
			if (match('/') && count == s.top())
				s.pop();

			count = 0; // Reset counter
		}

		else advance();
	}
}

/// Check if the character is a letter or an underscore
bool Lexer::isAlpha(const int c) {
    return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_';
}

/// Check if the character is a letter, an underscore or a digit
bool Lexer::isAlphaNum(const int c) {
	return isAlpha(c) || isDigit(c);
}

/// Check if the character is a digit
bool Lexer::isDigit(const int c) {
    return c >= '0' && c <= '9';
}

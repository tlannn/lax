#include "lexer/Lexer.h"
#include "lexer/LexError.h"
#include "tokens/Token.h"

std::string Lexer::currentFile;

/// Class constructor
Lexer::Lexer(const std::string& filename) :
    m_source(std::make_unique<std::ifstream>()),
    m_startIndex(-1),
    m_index(-1),
    m_line(1),
    m_col(0),
    m_startLine(1),
    m_startCol(0)
{
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
    reserve("fun", TokenType::FUN);
    reserve("return", TokenType::RETURN);
    reserve("include", TokenType::INCLUDE);

    openFile(filename);
}

/// Return the part containing the path to a file
std::string Lexer::getPath(const std::string& filepath) {
    size_t index = filepath.find_last_of('/');
    return filepath.substr(0, index + 1);
}

/// Open a stream to read a file and place the cursor at the beginning
void Lexer::openFile(const std::string& filename) {
    std::string filepath;

    // Determine the path to the file according to the paths to previous
    // files opened
    if (!m_mementos.empty()) {
        Memento* memento = &m_mementos.top();

        while (memento) {
            filepath.insert(0, getPath(memento->getSource()));
            memento = memento->getPrevious();
        }
    }

    // Close the old stream and open a new one to the file
    m_source->close();
    m_source->open(filepath + filename);

    if (!m_source->is_open())
        error("Could not open file '" + filename + "'");

    Lexer::currentFile = filename;

    // Reset all attributes
    m_startLine = 1;
    m_startCol = 0;
    m_line = 1;
    m_col = 0;
    m_index = -1;
}

/// Open a file and push it on top of the stack of files opened
void Lexer::pushFile(const std::string& filename) {
    m_mementos.emplace(
        !m_mementos.empty() ? &m_mementos.top() : nullptr,
        Lexer::currentFile, m_startIndex, m_startLine, m_startCol
    );

    openFile(filename);
}

/// Pop the last file opened and restore the state of the previous file
void Lexer::popFile() {
    Memento memento = m_mementos.top();
    openFile(memento.getSource());

    // Move cursor to old position in file, before the last token read
    m_source->seekg(memento.getIndex());

    m_line = memento.getLine();
    m_col = memento.getCol();
    m_index = memento.getIndex();

    // Delete the old memento
    m_mementos.pop();
}

/// Continue the reading of the source code and return the next token analyzed
std::unique_ptr<Token> Lexer::nextToken() {
    int c = advance();

    // Set the start position of the next token to the cursor current position
    m_startIndex = m_index;
    m_startCol = m_col;
    m_startLine = m_line;

    // Skip whitespaces, tabulations and newlines
    for (;; c = advance()) {
        if (c == ' ' || c == '\t') {
            // Anticipate advance()
            m_startCol = m_col + 1;
            m_startIndex = m_index + 1;
        } else if (c == '\n') {
            // Place cursor to the beginning of next line
            ++m_line;
            m_col = 0;
        } else break;
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
        case ',': return createToken(TokenType::COMMA);
        case '+': return createToken(TokenType::PLUS);
        case '-': return createToken(TokenType::MINUS);
        case '*': return createToken(TokenType::STAR);
        case '/':
            if (match('/')) {
                inlineComment();
                return nextToken();
            }
            else if (peek() == '*') {
                blockComment();
                return nextToken();
            }
            return createToken(TokenType::SLASH);
        case '&': if (match('&')) return createToken(TokenType::AND);
            break;
        case '|': if (match('|')) return createToken(TokenType::OR);
            break;
        case '!': return createToken(match('=') ? TokenType::NEQ : TokenType::BANG);
        case '=': return createToken(match('=') ? TokenType::EQ : TokenType::SIMEQ);
        case '<': return createToken(match('=') ? TokenType::LE : TokenType::SL);
        case '>': return createToken(match('=') ? TokenType::GE : TokenType::SG);
        case '"': return string();
        default:
            if (isDigit(c)) return number(c); // Recognize numbers
            else if (isAlpha(c)) return identifier(c); // Recognize words
    }

    return createToken(TokenType::UNKNOWN, std::string(1, static_cast<char>(c)));
}

/// Reserve a word, meaning it cannot be used as an identifier (for variables,
/// functions, classes, etc.)
void Lexer::reserve(const std::string& word, TokenType type) {
    m_words[word] = type;
}

/// Create a token of a specific type. The lexeme is deduced from the token type
UToken Lexer::createToken(TokenType type) {
    return createToken(type, Token::lexeme(type));
}

/// Create a token of specific type and lexeme
UToken Lexer::createToken(TokenType type, const std::string& lexeme) const {
    return std::make_unique<Token>(lexeme, type, m_startLine, m_startCol);
}

/// Throw an error
void Lexer::error(const std::string& message) const {
    throw LexError(
        Lexer::currentFile, m_startLine, m_startCol, message, "LexerError"
    );
}

/// Return whether the cursor is at the end of the current file
bool Lexer::isAtEnd() {
    return m_source->peek() == EOF;
}

/// Read a character in the source code and return it
int Lexer::advance() {
    ++m_index;
    ++m_col;
    return m_source->get();
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
    return m_source->peek();
}

/// Read a string in the source code
std::unique_ptr<Token> Lexer::string() {
    std::string buffer;
    int c;

    // Read in buffer all characters until closing quotation, end of file or
    // end of line
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

    return createToken(TokenType::STR, buffer);
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
    auto it = m_words.find(buffer);

    // If the word is already reserved, return it
    if (m_words.find(buffer) != m_words.end())
        return createToken(it->second, it->first);

    else {
        // Reserve this word as an identifier
        m_words[buffer] = TokenType::ID;
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
        // Increase line count on new lines
        if (peek() == '\n') m_line++;

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

            // Pop from the stack if the number of stars is the same as the
            // last tag in stack
            if (match('/') && count == s.top())
                s.pop();

            count = 0; // Reset counter
        } else advance();
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

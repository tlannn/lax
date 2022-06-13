#include "lexer.h"

int Lexer::line = 1;
int Lexer::col = 1;

/// Class constructor
Lexer::Lexer(std::string &source) : _source(source), _look(' '), _index(-1) {
    // Reserve words
    reserve(&Word::TRUE); reserve(&Word::FALSE);
    reserve(&Word::AND); reserve(&Word::OR);
    reserve(&Word::EQ); reserve(&Word::NEQ);
    reserve(&Word::LE); reserve(&Word::GE);
    reserve(&Word::SL); reserve(&Word::SG);
    reserve(&Word::IF); reserve(&Word::ELSE);
    reserve(&Word::PRINT);
}

/// Continue the reading of the source code and return the next token analyzed
Token* Lexer::nextToken() {
    // Skip whitespaces, tabulations and newlines
    for (; ; readChar()) {
        if (_look == ' ' || _look == '\t') continue;
        else if (_look == '\n') { Lexer::line++; Lexer::col = 1; }
        else break;
    }

    // Recognize boolean and relational operators
    switch (_look) {
        case '&':
            if (readChar('&')) return &Word::AND;
            break;
        case '|':
            if (readChar('|')) return &Word::OR;
            break;
        case '=':
            if (readChar('=')) return &Word::EQ;
            break;
        case '!':
            if (readChar('=')) return &Word::NEQ;
            break;
        case '<':
            if (readChar('=')) return &Word::LE; else return &Word::SL;
            break;
        case '>':
            if (readChar('=')) return &Word::GE; else return &Word::SG;
            break;
    }

    // Recognize numbers
    if (isDigit(&_look)) {
        int n = 0;
        do {
            n = 10 * n + (int)_look - '0'; readChar();
        } while (isDigit(&_look));

        return new Num(n);
    }

    // Recognize operators
    else if (isOperator(&_look)) {
        Op *op = new Op(std::string(1, _look));
        _look = ' ';
        return op;
    }

    // Recognize parenthesis
    else if (isParenthesis(&_look)) {
        Token *tok = new Token(std::string(1, _look), _look == '(' ? TokenType::LPAREN : TokenType::RPAREN);
        _look = ' ';
        return tok;
    }

    // Recognize words
    else if (isLetter(&_look)) {
        // Read in a buffer all following letters
        std::string buffer = "";
        do {
            buffer += _look; readChar();
        } while (isLetter(&_look));

        // If the word is already reserved, return it
        std::unordered_map<std::string, Word*>::iterator it = _words.find(buffer);
        if (it != _words.end())
            return it->second;

        // Reserve this word as an identifier
        Word *word = new Word(buffer, TokenType::ID);
        reserve(word);
        return word;
    }

    // Recognize semicolons
    else if (isSemicolon(&_look)) {
        Token *tok = new Token(std::string(1, _look), TokenType::SEMICOL);
        _look = ' ';
        return tok;
    }

    // Executed if end of file reached
    return new Token(TokenType::END);
}

/// Reserve a word, meaning it cannot be used as an identifier
void Lexer::reserve(Word *word) {
    _words[word->toString()] = word;
}

/// Read a character in the source code and update the current token
void Lexer::readChar() {
    Lexer::col++;
    _index++;

    if (_index < _source.length())
        _look = _source.at(_index);
    else _look = EOF;
}

/// Read a character in the source code and check if it is the expected one
bool Lexer::readChar(char expected) {
    readChar();
    if (_look != expected) return false;
    _look = ' ';
    return true;
}

/// Check if the character is a letter
bool Lexer::isLetter(const char *c) {
    return *c >= 'A' && *c <= 'Z' || *c >= 'a' && *c <= 'z';
}

/// Check if the character is a digit
bool Lexer::isDigit(const char *c) {
    return *c >= '0' && *c <= '9';
}

/// Check if the character is an operator
bool Lexer::isOperator(const char *c) {
    return *c == '+' || *c == '-' || *c == '*' || *c == '/';
}

/// Check if the character is an opening or closed parenthesis
bool Lexer::isParenthesis(const char *c) {
    return *c == '(' || *c == ')';
}

/// Check if the character is a semicolon
bool Lexer::isSemicolon(const char *c) {
    return *c == ';';
}

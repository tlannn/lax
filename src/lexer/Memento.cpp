#include "lexer/Memento.h"

#include <utility>

/// Class constructor
Memento::Memento(Memento* previous, std::string source, int index,
    int line, int col) :
    m_previous(previous),
    m_source(std::move(source)),
    m_index(index),
    m_line(line),
    m_col(col) {}

/// Getter for the previous memento
Memento* Memento::getPrevious() const {
    return m_previous;
}

/// Getter for the source file name
const std::string& Memento::getSource() const {
    return m_source;
}

/// Getter for the current index in the source code
int Memento::getIndex() const {
    return m_index;
}

/// Getter for the current line in the source code
int Memento::getLine() const {
    return m_line;
}

/// Getter for the current column in the source code
int Memento::getCol() const {
    return m_col;
}

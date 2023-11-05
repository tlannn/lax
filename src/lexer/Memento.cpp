#include "lexer/Memento.h"

#include <utility>

Memento::Memento(Memento* previous, std::string source, int index,
    int line, int col) :
    m_previous(previous),
    m_source(std::move(source)),
    m_index(index),
    m_line(line),
    m_col(col) {}

Memento* Memento::getPrevious() const {
    return m_previous;
}

const std::string& Memento::getSource() const {
    return m_source;
}

int Memento::getIndex() const {
    return m_index;
}

int Memento::getLine() const {
    return m_line;
}

int Memento::getCol() const {
    return m_col;
}

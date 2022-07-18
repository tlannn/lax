#include "memento.h"

/// Class constructor
Memento::Memento(Memento *previous, const std::string &source, int index, int line, int col) :
	_previous(previous), _source(source), _index(index), _line(line), _col(col) {}

/// Getter for the previous memento
Memento *Memento::getPrevious() const {
	return _previous;
}

/// Getter for the source file name
const std::string &Memento::getSource() const {
	return _source;
}

/// Getter for the current index in the source code
int Memento::getIndex() const {
	return _index;
}

/// Getter for the current line in the source code
int Memento::getLine() const {
	return _line;
}

/// Getter for the current column in the source code
int Memento::getCol() const {
	return _col;
}

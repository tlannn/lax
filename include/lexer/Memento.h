#ifndef LAX_MEMENTO_H
#define LAX_MEMENTO_H

#include <memory>
#include <string>

/**
 * Memento to remind to state of the previous file being analyzed by the lexer
 *
 * During lexical analysis, another source file can be reached and so the
 * current file being processed must be put on hold. In that case, the new file
 * is put on top of the stack of file processed.
 * The memento keeps information about one file in the stack, like the last
 * position in the file, as well as a pointer to the memento of the previous
 * file in the stack
 */
class Memento {
public:
    /**
     * Class constructor
     * @param previous the previous memento
     * @param source the name of the source file
     * @param index the current index in the file
     * @param line the current line in the file
     * @param col the current column in the file
     */
    Memento(Memento* previous, std::string source, int index, int line, int col);

    /**
     * Getter for the previous memento
     * @return the previous memento
     */
    Memento* getPrevious() const;

    /**
     * Getter for the source file name
     * @return the source file
     */
    const std::string& getSource() const;

    /**
     * Getter for the current index in the source code
     * @return the index
     */
    int getIndex() const;

    /**
     * Getter for the current line in the source code
     * @return the line
     */
    int getLine() const;

    /**
     * Getter for the current column in the source code
     * @return the column
     */
    int getCol() const;

private:
    Memento* m_previous;
    std::string m_source;
    int m_index;
    int m_line;
    int m_col;
};

#endif // LAX_MEMENTO_H

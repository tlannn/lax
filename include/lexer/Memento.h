#ifndef LAX_MEMENTO_H
#define LAX_MEMENTO_H

#include <memory>
#include <string>

/**
 * @class Memento
 * @brief A memento of a file's current state of lexical analysis.
 *
 * During lexical analysis, another source file can be reached and so the
 * current file being processed must be put on hold. In that case, the new file
 * is put on top of the stack of file processed.
 *
 * The memento keeps information about one file in the stack, like the last
 * position in the file, as well as a pointer to the memento of the previous
 * file in the stack.
 */
class Memento {
public:
    /**
     * @Brief Class constructor.
     * @param previous The previous memento.
     * @param source The filename of the source file.
     * @param index The current index in the file.
     * @param line The current line in the file.
     * @param col The current column in the file.
     */
    Memento(Memento* previous, std::string source, int index, int line, int col);

    /**
     * @brief Retrieves the previous element in the data structure.
     *
     * This method returns the previous element relative to the current element
     * in the data structure.
     * It does not modify the data structure in any way.
     *
     * @return The previous element in the data structure.
     */
    Memento* getPrevious() const;


    /**
     * @brief Returns the filename of the source code.
     *
     * This function provides access to the filename of the source code in a
     * read-only manner. It returns a constant reference to prevent any
     * modifications to the filename.
     *
     * @return A constant reference to the filename.
     */
    const std::string& getSource() const;

    /**
     * @brief Returns the current index in the source code.
     * @return The current index in the source code.
     */
    int getIndex() const;

    /**
     * @brief Returns the current line in the source code.
     * @return The current line in the source code.
     */
    int getLine() const;

    /**
     * @brief Returns the current column in the source code.
     * @return The current column in the source code.
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

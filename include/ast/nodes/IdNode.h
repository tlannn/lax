#ifndef LAX_IDNODE_H
#define LAX_IDNODE_H

#include <memory>

#include "ExprNode.h"

// Forward declarations
class ASTVisitor;
class Symbol;
class Token;
class ObjString;

typedef std::shared_ptr<Token> SToken;

/**
 * @class IdNode
 * @brief Represents an identifier in the Abstract Syntax Tree (AST).
 *
 * The IdNode class is used to store information about an identifier, which is
 * a name that refers to a variable, function, or class.
 */
class IdNode : public ExprNode {
public:
    /**
     * @brief Class constructor.
     * @param id The token representing the identifier.
     */
    explicit IdNode(SToken id);

    /**
     * @brief Retrieves the identifier associated with this node.
     * @return The identifier associated with this node.
     */
    ObjString* getName();

    /**
     * @brief Retrieves the symbol associated with this node.
     * @return The symbol associated with this node.
     *
     * @see setSymbol()
     */
    Symbol* getSymbol() const;

    /**
     * @brief Associates a symbol with this node.
     * @param symbol The symbol to associate with this node.
     *
     * @see getSymbol()
     */
    void setSymbol(Symbol* symbol);

    /**
     * @copydoc ASTNode::accept()
     */
    void accept(ASTVisitor& visitor) override;

private:
    ObjString* m_name;
    Symbol* m_symbol;
};

#endif // LAX_IDNODE_H

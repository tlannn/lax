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
 * Node for an identifier
 *
 * An identifier represents a variable name. Whenever it appears in the code,
 * it is replaced by the current value of the variable defined by this
 * identifier.
 */
class IdNode : public ExprNode {
public:
    /**
     * Class constructor
     *
     * @param id the identifier name token
     */
    explicit IdNode(SToken id);

    /**
     * Getter for the name of the identifier
     *
     * @return the name
     */
    ObjString* getName();

    /**
     * Getter for the symbol representing the variable referred to
     * @return a pointer to the symbol
     */
    Symbol* getSymbol() const;

    /**
     * Setter for the symbol representing the variable referred to
     * @param symbol a pointer to the symbol
     */
    void setSymbol(Symbol* symbol);

    /**
     * Accept method for the visitor pattern
     */
    void accept(ASTVisitor& visitor) override;

private:
    ObjString* m_name;
    Symbol* m_symbol;
};

#endif // LAX_IDNODE_H

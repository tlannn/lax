#ifndef LAX_CALLNODE_H
#define LAX_CALLNODE_H

#include <memory>
#include <vector>

#include "ExprNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;
class Symbol;

/**
 * @class CallNode
 * @brief Represents a function or method call expression node.
 *
 * The CallNode class holds information about a function or method call, such as
 * the callee (the entity being called), and the arguments passed to the call.
 */
class CallNode : public ExprNode {
public:
    /**
     * @brief Class constructor.
     * @param callee The callee expression.
     * @param token The token representing the call.
     * @param args The arguments passed to the call.
     */
    CallNode(UExprNode callee, UToken token, std::vector<UExprNode> args);

    /**
     * @brief Returns the name of the callee of the current function.
     *
     * This function retrieves the expression node that represents the name
     * of the function that is being called.
     *
     * @return The callee expression of the current function.
     */
    ExprNode* getCallee();

    /**
     * @brief Returns the arguments passed to the current function.
     *
     * This function retrieves the arguments that were passed to the current
     * function and returns them as a vector of expression nodes.
     *
     * @return The arguments passed to the current function.
     */
    const std::vector<UExprNode>& getArgs();

    /**
     * @brief Returns the symbol associated with the current object.
     *
     * This function retrieves the symbol that represents the function that is
     * associated with the current object.
     * The symbol provides information about the function, such as its name,
     * parameters and return type. The symbol is used to identify the function.
     *
     * @return The symbol associated with the current object.
     *
     * @see setSymbol()
     */
    Symbol* getSymbol() const;

    /**
     * @brief Sets the symbol of the variable associated with this node.
     * @param symbol The symbol to set.
     *
     * @see getSymbol()
     */
    void setSymbol(Symbol* symbol);

    /**
     * @copydoc ASTNode::accept()
     */
    void accept(ASTVisitor& visitor) override;

private:
    UExprNode m_callee;
    std::vector<UExprNode> m_args;
    Symbol* m_symbol;
};

#endif // LAX_CALLNODE_H

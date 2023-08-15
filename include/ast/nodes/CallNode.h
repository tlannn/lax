#ifndef LAX_CALLNODE_H
#define LAX_CALLNODE_H

#include <memory>
#include <vector>

#include "ExprNode.h"
#include "ast/ASTFwdDecl.h"

// Forward declarations
class ASTVisitor;
class Symbol;
class Token;

typedef std::shared_ptr<Token> SToken;

/**
 * Node for a function call
 *
 * Call a function and execute the statements in its body. If the function
 * expects parameters, then values specified during the call are passed to the
 * function in the same order as they appear.
 * The function must be declared and defined before it can be called.
 */
class CallNode : public ExprNode {
public:
	/**
	 * Class constructor
	 *
	 * @param callee the expression that is called
	 * @param token the closing parenthesis token
	 * @param args the list of arguments
	 */
	CallNode(UExprNode callee, SToken token, std::vector<UExprNode> args);

	/**
	 * Getter for the callee
	 *
	 * @return the callee
	 */
	ExprNode* getCallee();

	/**
	 * Getter for the arguments of the call
	 *
	 * @return the arguments
	 */
	const std::vector<UExprNode>& getArgs();

    /**
     * Getter for the symbol representing the function called
     * @return a pointer to the symbol
     */
    Symbol* getSymbol() const;

    /**
     * Setter for the symbol representing the function called
     * @param symbol a pointer to the symbol
     */
    void setSymbol(Symbol *symbol);

	/**
	 * Accept method for the visitor pattern
	 */
    void accept(ASTVisitor &visitor) override;

private:
	UExprNode _callee;
	std::vector<UExprNode> _args;
    Symbol *_symbol;
};

#endif // LAX_CALLNODE_H

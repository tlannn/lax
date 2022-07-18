#ifndef LAX_ID_H
#define LAX_ID_H

#include "exprnode.h"
#include "interpreter/astvisitor.h"
#include "tokens/token.h"

/**
 * Node for an identifier
 *
 * An identifier represents a variable name. Whenever it appears in the code,
 * it is replaced by the current value of the variable defined by this
 * identifier.
 */
class Id : public ExprNode {
public:
	/**
	 * Class constructor
	 *
	 * @param word the word defining the identifier
	 */
    explicit Id(Token *word);

	/**
	 * Accept method for the visitor pattern
	 */
	void accept(ASTVisitor *visitor) override;
};

#endif // LAX_ID_H

#ifndef LAX_ID_H
#define LAX_ID_H

#include "exprnode.h"
#include "tokens/word.h"
#include "tokens/type.h"

/*
 * Forward declarations for cyclic dependencies
 */
class ExprNode;
class ExprVisitor;

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
    Id(Word word);

	/**
	 * Accept method for the visitor pattern
	 */
    int accept(ExprVisitor *visitor) override;
};

#endif // LAX_ID_H

#ifndef LAX_DECLNODE_H
#define LAX_DECLNODE_H

#include <memory>

#include "astvisitor.h"
#include "exprnode.h"
#include "stmtnode.h"
#include "common/valuetype.h"
#include "tokens/token.h"

/**
 * Node for variable declaration statements
 *
 * When declaring a variable, its name and type must be specified. The variable
 * can be initialized at declaration ; in that case, an expression is
 * associated to the node
 */
class DeclNode : public StmtNode {
public:
	/**
	 * Class constructor
	 *
	 * @param id the name of the variable declared
	 * @param type the type of the variable
	 * @param expr the expression associated to the variable (if any)
	 */
    DeclNode(std::shared_ptr<Token> id, ValueType type, std::unique_ptr<ExprNode> expr);

	/**
     * Getter for the name of the variable declared
     *
     * @return the name of the variable
     */
	std::shared_ptr<Token> getId();

	/**
     * Getter for the type of the variable declared
     *
     * @return the type of the variable
     */
    ValueType getType();

	/**
     * Getter for the expression associated to the variable at declaration
     *
     * @return the expression associated, or nullptr if the variable is not
     * initialized at declaration
     */
	ExprNode* getRValue();

	/**
     * Accept method for the visitor pattern
     */
    void accept(ASTVisitor *visitor) override;

private:
	std::shared_ptr<Token> _id;
    ValueType _type;
	std::unique_ptr<ExprNode> _rvalue;
};

#endif // LAX_DECLNODE_H

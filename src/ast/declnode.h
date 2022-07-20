#ifndef LAX_DECLNODE_H
#define LAX_DECLNODE_H

#include <memory>

#include "exprnode.h"
#include "stmtnode.h"
#include "interpreter/astvisitor.h"
#include "tokens/token.h"
#include "tokens/type.h"

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
    DeclNode(std::shared_ptr<Token> id, Type type, std::unique_ptr<ExprNode> expr);

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
    Type getType();

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
    Type _type;
	std::unique_ptr<ExprNode> _rvalue;
};

#endif // LAX_DECLNODE_H

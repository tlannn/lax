#ifndef LAX_DECLNODE_H
#define LAX_DECLNODE_H

#include <string>

#include "exprnode.h"
#include "stmtnode.h"
#include "interpreter/stmtvisitor.h"
#include "tokens/type.h"

/**
 * Node for variable declaration statements
 *
 * When declaring a variable, its name and type must be specified. The variable
 * can be initialized at declaration ; int that case, an expression is
 * associated to the node
 */
class DeclNode : public StmtNode {
public:
	/**
	 * Class constructor
	 *
	 * @param name the name of the variable declared
	 * @param type the type of the variable
	 * @param expr the expression associated to the variable (if any)
	 */
    DeclNode(std::string name, Type type, ExprNode *expr);

	/**
     * Getter for the name of the variable declared
     *
     * @return the name of the variable
     */
    std::string getName();

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
    void accept(StmtVisitor *visitor) override;

private:
    std::string _name;
    Type _type;
    ExprNode *_rvalue;
};

#endif // LAX_DECLNODE_H

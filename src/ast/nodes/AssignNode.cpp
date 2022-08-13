#include "ast/nodes/AssignNode.h"
#include "ast/ASTVisitor.h"
#include "tokens/Token.h"

/// Class constructor
AssignNode::AssignNode(UExprNode identifier, UExprNode expr) :
						ExprNode(identifier->getToken()), _identifier(std::move(identifier)), _expr(std::move(expr)) {}

/// Getter for the token of the variable
std::string AssignNode::getName() {
    return _identifier->getToken()->toString();
}

/// Getter for the new expression assigned
ExprNode* AssignNode::getExpr() {
    return _expr.get();
}

/// Accept method for the visitor pattern
void AssignNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

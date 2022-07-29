#include "assignnode.h"

/// Class constructor
AssignNode::AssignNode(std::unique_ptr<ExprNode> identifier, std::unique_ptr<ExprNode> expr) :
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

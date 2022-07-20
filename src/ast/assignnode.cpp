#include "assignnode.h"

/// Class constructor
AssignNode::AssignNode(std::unique_ptr<Token> id, std::unique_ptr<ExprNode> expr) : StmtNode(),
	_id(std::move(id)), _expr(std::move(expr)) {}

/// Getter for the token of the variable
Token* AssignNode::getToken() {
    return _id.get();
}

/// Getter for the new expression assigned
ExprNode* AssignNode::getExpr() {
    return _expr.get();
}

/// Accept method for the visitor pattern
void AssignNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

#include "assignnode.h"

/// AssignNode constructor
AssignNode::AssignNode(Token *id, ExprNode *expr) : StmtNode(), _id(id), _expr(expr) {}

/// Getter for the token of the variable
Token* AssignNode::getToken() {
    return _id;
}

/// Getter for the new expression assigned
ExprNode* AssignNode::getExpr() {
    return _expr;
}

/// Accept method for the visitor pattern
void AssignNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

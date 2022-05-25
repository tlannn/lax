#include "ifnode.h"

/// IfNode constructor
IfNode::IfNode(ExprNode *expr, StmtNode *stmt) : _expr(expr), _stmt(stmt) {
    if (expr->getType() != Type::BOOL)
        std::cout << "boolean required in if" << std::endl;
}

/// Getter for the condition expression
ExprNode* IfNode::getConditionExpression() {
    return _expr;
}

/// Getter for the 'then' statement
StmtNode* IfNode::getThenStatement() {
    return _stmt;
}

/// Accept method for the visitor pattern
void IfNode::accept(StmtVisitor *visitor) {
    visitor->visit(this);
}

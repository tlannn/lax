#include "conditionalnode.h"

/// ConditionalNode constructor
ConditionalNode::ConditionalNode(ExprNode *expr, StmtNode *thenStmt, StmtNode *elseStmt) :
_expr(expr), _thenStmt(thenStmt), _elseStmt(elseStmt) {
    if (expr->getType() != Type::BOOL)
        std::cout << "boolean required in if" << std::endl;
}

/// Getter for the condition expression
ExprNode* ConditionalNode::getConditionExpression() {
    return _expr;
}

/// Getter for the 'then' statement
StmtNode* ConditionalNode::getThenStatement() {
    return _thenStmt;
}

/// Getter for the 'else' statement
StmtNode* ConditionalNode::getElseStatement() {
    return _elseStmt;
}

/// Accept method for the visitor pattern
void ConditionalNode::accept(StmtVisitor *visitor) {
    visitor->visit(this);
}

#include "relationalnode.h"

/// RelationalNode constructor
RelationalNode::RelationalNode(ExprNode *left, Token *op, ExprNode *right) : LogicalNode(left, op, right) {}

/// Accept method for the visitor pattern
void RelationalNode::accept(ASTVisitor *visitor) {
    visitor->visit(this);
}

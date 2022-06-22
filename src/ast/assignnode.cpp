#include "assignnode.h"

AssignNode::AssignNode(std::string id, ExprNode *expr) : StmtNode(), _id(id), _expr(expr) {}

std::string AssignNode::getLValue() {
    return _id;
}

ExprNode* AssignNode::getRValue() {
    return _expr;
}

void AssignNode::accept(StmtVisitor *visitor) {
    visitor->visit(this);
}

#include "ast/nodes/CallNode.h"
#include "ast/ASTVisitor.h"

CallNode::CallNode(UExprNode callee, SToken token, std::vector<UExprNode> args) :
    ExprNode(std::move(token)),
    m_callee(std::move(callee)),
    m_args(std::move(args)),
    m_symbol(nullptr) {}

ExprNode* CallNode::getCallee() {
    return m_callee.get();
}

const std::vector<UExprNode>& CallNode::getArgs() {
    return m_args;
}

Symbol* CallNode::getSymbol() const {
    return m_symbol;
}

void CallNode::setSymbol(Symbol* symbol) {
    m_symbol = symbol;
}

void CallNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

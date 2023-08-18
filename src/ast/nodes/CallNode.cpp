#include "ast/nodes/CallNode.h"
#include "ast/ASTVisitor.h"

/// Class constructor
CallNode::CallNode(UExprNode callee, SToken token, std::vector<UExprNode> args) :
    ExprNode(std::move(token)),
    m_callee(std::move(callee)),
    m_args(std::move(args)),
    m_symbol(nullptr) {}

/// Getter for the callee
ExprNode* CallNode::getCallee() {
    return m_callee.get();
}

/// Getter for the arguments of the call
const std::vector<UExprNode>& CallNode::getArgs() {
    return m_args;
}

/// Getter for the symbol representing the function called
Symbol* CallNode::getSymbol() const {
    return m_symbol;
}

/// Setter for the symbol representing the function called
void CallNode::setSymbol(Symbol* symbol) {
    m_symbol = symbol;
}

/// Accept method for the visitor pattern
void CallNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

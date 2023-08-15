#include "ast/nodes/CallNode.h"
#include "ast/ASTVisitor.h"
#include "tokens/Token.h"

/// Class constructor
CallNode::CallNode(
    UExprNode callee,
    SToken token,
    std::vector<UExprNode> args
) : ExprNode(std::move(token)),
    _callee(std::move(callee)),
    _args(std::move(args)),
    _symbol(nullptr) {}

/// Getter for the callee
ExprNode* CallNode::getCallee() {
	return _callee.get();
}

/// Getter for the arguments of the call
const std::vector<UExprNode>& CallNode::getArgs() {
	return _args;
}

/// Getter for the symbol representing the function called
Symbol* CallNode::getSymbol() const {
    return _symbol;
}

/// Setter for the symbol representing the function called
void CallNode::setSymbol(Symbol *symbol) {
    _symbol = symbol;
}

/// Accept method for the visitor pattern
void CallNode::accept(ASTVisitor &visitor) {
    visitor.visit(*this);
}

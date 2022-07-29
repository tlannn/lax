#include "funnode.h"

/// Class constructor
FunNode::FunNode(std::unique_ptr<Token> name, ValueType type,
				 std::vector<std::unique_ptr<Variable>> params, std::unique_ptr<BlockNode> body) : StmtNode(),
				 _name(std::move(name)), _type(type), _params(std::move(params)), _body(std::move(body)) {}

/// Getter for the return type of the function
ValueType FunNode::getType() {
	return _type;
}

/// Getter for the function name
Token* FunNode::getName() {
	return _name.get();
}

/// Getter for the function body
BlockNode* FunNode::getBody() {
	return _body.get();
}

/// Getter for the function parameters
const std::vector<std::unique_ptr<Variable>>& FunNode::getParams() {
	return _params;
}

/// Accept method for the visitor pattern
void FunNode::accept(ASTVisitor *visitor) {
	visitor->visit(this);
}

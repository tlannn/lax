#include "ast/nodes/FunNode.h"
#include "ast/nodes/BlockNode.h"
#include "ast/nodes/SeqNode.h"
#include "ast/ASTVisitor.h"
#include "objects/Variable.h"

/// Class constructor
FunNode::FunNode(UToken token, ObjString *name, LaxType *returnType,
				 std::vector<UVariable> params, UBlockNode body) :
				 StmtNode(), _token(std::move(token)), _name(name),
				 _returnType(returnType), _params(std::move(params)),
				 _body(std::move(body)) {}

/// Getter for the function token
Token* FunNode::getToken() {
	return _token.get();
}

/// Getter for the function name
ObjString* FunNode::getName() {
	return _name;
}

/// Getter for the return type of the function
LaxType* FunNode::getReturnType() {
	return _returnType;
}

/// Getter for the function body
BlockNode* FunNode::getBody() {
	return _body.get();
}

/// Getter for the function parameters
const std::vector<UVariable>& FunNode::getParams() {
	return _params;
}

/// Getter for the symbol representing the function
FunSymbol *FunNode::getSymbol() {
	return _symbol;
}

/// Setter for the symbol representing the function
void FunNode::setSymbol(FunSymbol *symbol) {
	_symbol = symbol;
}

/// Accept method for the visitor pattern
void FunNode::accept(ASTVisitor &visitor) {
    visitor.visit(*this);
}

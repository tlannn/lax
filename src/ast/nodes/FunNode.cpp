#include "ast/nodes/FunNode.h"
#include "ast/nodes/BlockNode.h"
#include "ast/nodes/SeqNode.h"
#include "ast/ASTVisitor.h"
#include "objects/Variable.h"

/// Class constructor
FunNode::FunNode(UToken token, ObjString* name, LaxType* returnType,
    std::vector<UVariable> params, UBlockNode body) :
    m_token(std::move(token)),
    m_name(name),
    m_returnType(returnType),
    m_params(std::move(params)),
    m_body(std::move(body)),
    m_symbol(nullptr) {}

/// Getter for the function token
Token* FunNode::getToken() {
    return m_token.get();
}

/// Getter for the function name
ObjString* FunNode::getName() {
    return m_name;
}

/// Getter for the return type of the function
LaxType* FunNode::getReturnType() {
    return m_returnType;
}

/// Getter for the function body
BlockNode* FunNode::getBody() {
    return m_body.get();
}

/// Getter for the function parameters
const std::vector<UVariable>& FunNode::getParams() {
    return m_params;
}

/// Getter for the symbol representing the function
FunSymbol* FunNode::getSymbol() {
    return m_symbol;
}

/// Setter for the symbol representing the function
void FunNode::setSymbol(FunSymbol* symbol) {
    m_symbol = symbol;
}

/// Accept method for the visitor pattern
void FunNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

#include "ast/nodes/FunNode.h"
#include "ast/nodes/BlockNode.h"
#include "ast/nodes/SeqNode.h"
#include "ast/ASTVisitor.h"
#include "objects/Variable.h"

FunNode::FunNode(UToken token, ObjString* name, LaxType* returnType,
    std::vector<UVariable> params, UBlockNode body) :
    m_token(std::move(token)),
    m_name(name),
    m_returnType(returnType),
    m_params(std::move(params)),
    m_body(std::move(body)),
    m_symbol(nullptr) {}

Token* FunNode::getToken() {
    return m_token.get();
}

ObjString* FunNode::getName() {
    return m_name;
}

LaxType* FunNode::getReturnType() {
    return m_returnType;
}

BlockNode* FunNode::getBody() {
    return m_body.get();
}

const std::vector<UVariable>& FunNode::getParams() {
    return m_params;
}

FunSymbol* FunNode::getSymbol() {
    return m_symbol;
}

void FunNode::setSymbol(FunSymbol* symbol) {
    m_symbol = symbol;
}

void FunNode::accept(ASTVisitor& visitor) {
    visitor.visit(*this);
}

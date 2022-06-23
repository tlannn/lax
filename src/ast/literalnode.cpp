#include "literalnode.h"

/// ConstantNode constructor
LiteralNode::LiteralNode(Token tok, Type type) : ExprNode(tok), _type(type) {}

/// ConstantNode constructor
LiteralNode::LiteralNode(int i) : ExprNode(Num(i)), _type(Type::INT) {}

/// Getter for the value of the literal
int LiteralNode::getValue() {
    if (_type == Type::INT)
        return stoi(_tok.toString());
    else if (_type == Type::BOOL)
        return _tok.toString() == Word::TRUE.toString() ? 1 : 0;

    return -1;
}

/// Getter for the type of the literal
Type LiteralNode::getType() {
	return _type;
}

/// Accept method for the visitor pattern
int LiteralNode::accept(ExprVisitor *visitor) {
    return visitor->visit(this);
}

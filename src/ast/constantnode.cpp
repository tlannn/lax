#include "constantnode.h"

/// ConstantNode constructor
ConstantNode::ConstantNode(Token tok, Type type) : ExprNode(tok), _type(type) {}

/// ConstantNode constructor
ConstantNode::ConstantNode(int i) : ExprNode(Num(i)), _type(Type::INT) {}

/// Getter for the value of the constant
int ConstantNode::getValue() {
    if (_type == Type::INT)
        return stoi(_tok.toString());
    else if (_type == Type::BOOL)
        return _tok.toString() == Word::TRUE.toString() ? 1 : 0;

    return -1;
}

/// Getter for the type of the constant
Type ConstantNode::getType() {
	return _type;
}

/// Accept method for the visitor pattern
int ConstantNode::accept(ExprVisitor *visitor) {
    return visitor->visit(this);
}

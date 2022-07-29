#include "common/ValueType.h"

/// Class constructor
ValueType::ValueType(ValueType::Type type) : _type(type) {}

/// Check whether a type is numeric or not
bool ValueType::isNumeric(const ValueType::Type &t) {
	return t == ValueType::VAL_INT;
}

/// Determine the wider type in a binary operation
ValueType::Type ValueType::max(const ValueType::Type &t1, const Token &op, const ValueType::Type &t2) {
	if (!isNumeric(t1) || !isNumeric(t2)) return ValueType::VAL_NULL;

	switch (op.getType()) {
		// Arithmetic operators
		case TokenType::PLUS:
			return addOpLookup[t1][t2];
		case TokenType::MINUS:
			return subOpLookup[t1][t2];
		case TokenType::STAR:
			return mulOpLookup[t1][t2];
		case TokenType::SLASH:
			return divOpLookup[t1][t2];
		// Logical operators
		case TokenType::OR:
		case TokenType::AND:
			return logicOpLookup[t1][t2];
		case TokenType::SG:
		case TokenType::SL:
		case TokenType::GE:
		case TokenType::LE:
		case TokenType::EQ:
		case TokenType::NEQ:
			return relOpLookup[t1][t2];
		default:
			return ValueType::VAL_NULL;
	}
}

/// Return the type from a token representing a type keyword
ValueType::Type ValueType::getType(Token *tok) {
	if (tok->toString() == ValueType::toString(ValueType::VAL_INT))
		return ValueType::VAL_INT;
	else if (tok->toString() == ValueType::toString(ValueType::VAL_BOOL))
		return ValueType::VAL_BOOL;
	else
		return ValueType::VAL_NULL;
}

/// Return a string representation of a type
std::string ValueType::toString(const ValueType &t) {
	switch (t) {
		case ValueType::VAL_NULL:
			return "null";
		case ValueType::VAL_BOOL:
			return "bool";
		case ValueType::VAL_INT:
			return "int";
		case ValueType::VAL_OBJ:
			return "obj";
	}

	return "";
}

/// Allow the use the type in a switch statement
ValueType::operator Type() const {
	return _type;
}

/// Overload the behavior of the assign operator when the assigned value is
/// a type object
ValueType& ValueType::operator=(const ValueType &t) {
	if (this == &t)
		return *this;

	_type = t;

	return *this;
}

/// Overload the behavior of the assign operator when the assigned value is
/// an enumeration type value
ValueType& ValueType::operator=(const ValueType::Type &t) {
	_type = t;

	return *this;
}

/// Overload the behavior of the equality operator
bool operator==(ValueType t1, ValueType::Type t2) {
	return t1._type == t2;
}

/// Overload the behavior of the non-equality operator
bool operator!=(ValueType t1, ValueType::Type t2) {
	return t1._type != t2;
}

/// Lookup tables for operations
ValueType::Type ValueType::addOpLookup[3][3] = {
	/*					null			bool 		int */
	/* null */ { VAL_NULL, VAL_NULL, VAL_NULL },
	/* bool */ { VAL_NULL, VAL_BOOL, VAL_NULL },
	/* int  */ { VAL_NULL, 	VAL_NULL, VAL_INT }
};

ValueType::Type ValueType::subOpLookup[3][3] = {
	/*					null			bool 		int */
	/* null */ { VAL_NULL, VAL_NULL, VAL_NULL },
	/* bool */ { VAL_NULL, VAL_BOOL, VAL_NULL },
	/* int  */ { VAL_NULL, 	VAL_NULL, VAL_INT }
};

ValueType::Type ValueType::mulOpLookup[3][3] = {
	/*					null			bool 		int */
	/* null */ { VAL_NULL, VAL_NULL, VAL_NULL },
	/* bool */ { VAL_NULL, VAL_BOOL, VAL_NULL },
	/* int  */ { VAL_NULL, 	VAL_NULL, VAL_INT }
};

ValueType::Type ValueType::divOpLookup[3][3] = {
	/*					null			bool 		int */
	/* null */ { VAL_NULL, VAL_NULL, VAL_NULL },
	/* bool */ { VAL_NULL, VAL_BOOL, VAL_NULL },
	/* int  */ { VAL_NULL, 	VAL_NULL, VAL_INT }
};

ValueType::Type ValueType::logicOpLookup[3][3] = {
	/*					null			bool 		int */
	/* null */ { VAL_NULL, VAL_NULL, VAL_NULL },
	/* bool */ { VAL_NULL, VAL_BOOL, VAL_BOOL },
	/* int  */ { VAL_NULL, VAL_BOOL, VAL_BOOL }
};

ValueType::Type ValueType::relOpLookup[3][3] = {
	/*					null			bool 		int */
	/* null */ { VAL_NULL, VAL_NULL, VAL_NULL },
	/* bool */ { VAL_NULL, VAL_BOOL, VAL_NULL },
	/* int  */ { VAL_NULL,	VAL_NULL, VAL_BOOL }
};

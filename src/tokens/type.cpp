#include "type.h"

/// Type constructor
Type::Type(const std::string &word, TokenType type, int size) : Word(word, type), _size(size) {}

/// Getter for the type size
int Type::getSize() const {
    return _size;
}

/// Determine the wider type in a binary operation
Type Type::max(const Type &t1, const Token &op, const Type &t2) {
	int type1 = typeToInt(t1);
	int type2 = typeToInt(t2);

	// Arithmetic operators
	switch (op.toString().at(0)) {
		case '+':
			return intToType(addOpLookup[type1][type2]);
		case '-':
			return intToType(subOpLookup[type1][type2]);
		case '*':
			return intToType(mulOpLookup[type1][type2]);
		case '/':
			return intToType(divOpLookup[type1][type2]);
	}

	// Logical operators
	switch (op.getType()) {
		case TokenType::OR:
		case TokenType::AND:
			return intToType(logicOpLookup[type1][type2]);
		case TokenType::SG:
		case TokenType::SL:
		case TokenType::GE:
		case TokenType::LE:
		case TokenType::EQ:
		case TokenType::NEQ:
			return intToType(relOpLookup[type1][type2]);
	}

	return Type::NONE;
}

/// Convert a type to a integer value
int Type::typeToInt(const Type &type) {
	if (type == Type::INT)
		return _int;
	else if (type == Type::BOOL)
		return _bool;
	else
		return _undef;
}

/// Convert a type integer value to a type
Type Type::intToType(const int i) {
	switch (i) {
		case _int:
			return Type::INT;
		case _bool:
			return Type::BOOL;
		default:
			return Type::NONE;
	}
}

/// Overload the equality operator to compare two types
bool operator== (const Type &t1, const Type &t2) {
    return t1._text == t2._text && t1._type == t2._type && t1._size == t2._size;
}

/// Overload the not equal operator to compare two types
bool operator!= (const Type &t1, const Type &t2) {
    return !operator==(t1, t2);
}

/// Create basic types words
Type Type::NONE = Type("none", TokenType::TYPE, 4);
Type Type::INT = Type("int", TokenType::TYPE, 4);
Type Type::BOOL = Type("bool", TokenType::TYPE, 1);

/// Lookup tables for operations
int addOpLookup[2][2] = {
	/*					int				bool */
	/* int  */ { _int, 		_undef },
	/* bool */ { _undef, 	_bool }
};

int subOpLookup[2][2] = {
	/*					int				bool */
	/* int  */ { _int, 		_undef },
	/* bool */ { _undef, 	_bool }
};

int mulOpLookup[2][2] = {
	/*					int				bool */
	/* int  */ { _int, 		_undef },
	/* bool */ { _undef, 	_bool }
};

int divOpLookup[2][2] = {
	/*					int				bool */
	/* int  */ { _int, 		_undef },
	/* bool */ { _undef, 	_bool }
};

int logicOpLookup[2][2] = {
	/*					int				bool */
	/* int  */ { _bool, 	_bool },
	/* bool */ { _bool, 	_bool }
};

int relOpLookup[2][2] = {
	/*					int				bool */
	/* int  */ { _bool,		_undef },
	/* bool */ { _undef, 	_bool }
};

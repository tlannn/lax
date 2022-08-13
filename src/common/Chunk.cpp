#include "common/Chunk.h"
#include "common/Memory.h"

/// Class constructor.
Chunk::Chunk() : _count(0), _capacity(0), _code(nullptr) {}

/// Class destructor.
Chunk::~Chunk() {
	FREE_ARRAY(uint8_t, _code, _capacity);
}

/// Write a byte in the bytecode of the chunk.
void Chunk::writeByte(uint8_t byte) {
	if (_capacity < _count + 1) {
		uint16_t oldCapacity = _capacity;
		_capacity = GROW_CAPACITY(oldCapacity);
		_code = GROW_ARRAY(uint8_t, _code, oldCapacity, _capacity);
	}

	_code[_count] = byte;
	++_count;
}

/// Getter for a code in the bytecode.
///
/// Return the first code of the bytecode if no offset is provided.
uint8_t* Chunk::getCode(int offset) {
	return _code + offset;
}

/// Add a constant value in the constant pool of the chunk.
uint16_t Chunk::addConstant(Value value) {
	_constants.writeValue(value);
	return _constants.getCount() - 1;
}

/// Getter for a constant in the constant pool.
///
/// Return the first constant if no offset is provided.
const Value& Chunk::getConstant(int offset) {
	return _constants.getValue(offset);
}

/// Getter for the number of codes written in the bytecode.
uint16_t Chunk::getCount() const {
	return _count;
}

/// Return the number of constants in the constant pool.
int Chunk::getConstantCount() const {
	return _constants.getCount();
}

#ifndef LAX_CHUNK_H
#define LAX_CHUNK_H

#include <vector>

#include "Value.h"

/// Enumeration of the operation codes in bytecode
enum OpCode {
	OP_EXTENDED_ARG,
	OP_CONSTANT,
	OP_NULL,
	OP_TRUE,
	OP_FALSE,
	OP_POP,
	OP_DEFINE_GLOBAL,
	OP_GET_GLOBAL,
	OP_SET_GLOBAL,
	OP_GET_UPVALUE,
	OP_SET_UPVALUE,
	OP_GET_LOCAL,
	OP_SET_LOCAL,
	OP_EQUAL,
	OP_NOT_EQUAL,
	OP_LESS,
	OP_LESS_EQUAL,
	OP_GREATER,
	OP_GREATER_EQUAL,
	OP_ADD,
	OP_SUBTRACT,
	OP_MULTIPLY,
	OP_DIVIDE,
	OP_NOT,
	OP_NEGATE,
	OP_CALL,
	OP_CLOSURE,
	OP_CLOSE_UPVALUE,
	OP_JUMP,
	OP_JUMP_FALSE,
	OP_LOOP,
	OP_RETURN
};

/**
 * Chunk of bytecode.
 *
 * The bytecode chunk is composed of instructions, represented as a sequence of
 * codes. An instruction is composed of an OpCode that describes the action to
 * perform at runtime. An OpCode may be followed by an optional OpArg if needed.
 * OpArgs can be expanded to be encoded on multiple bytes using the
 * OP_EXTENDED_ARG OpCode.
 *
 * The chunk has a constant pool that keeps track of constant values used in the
 * bytecode. The index of a constant in the constant pool may be used as an
 * OpArg to refer to that value.
 */
class Chunk {
public:
	/// Class constructor.
	Chunk();

	/// Class destructor.
	~Chunk();

	/**
	 * Write a byte in the bytecode of the chunk.
	 *
	 * @param byte the byte to write.
	 */
	void writeByte(uint8_t byte);

	/**
	 * Getter for a code in the bytecode.
	 *
	 * Return the first code of the bytecode if no offset is provided.
	 *
	 * @param offset the offset of the code in the bytecode.
	 * @return a pointer to the code.
	 */
	uint8_t* getCode(int offset = 0);

	/**
	 * Add a constant value in the constant pool of the chunk.
	 *
	 * @param value the constant value to add.
	 * @return the index of the constant in the constant pool.
	 */
	uint16_t addConstant(Value value);

	/**
	 * Getter for a constant in the constant pool.
	 *
	 * Return the first constant if no offset is provided.
	 *
	 * @param offset the offset of the constant in the constant pool.
	 * @return a reference to the constant value in the constant pool.
	 */
	const Value& getConstant(int offset = 0);

	/**
	 * Getter for the number of codes written in the bytecode.
	 *
	 * @return the number of codes.
	 */
	uint16_t getCount() const;

	/**
	 * Return the number of constants in the constant pool.
	 *
	 * @return the number of constants.
	 */
	int getConstantCount() const;

private:
	uint16_t _count;
	uint16_t _capacity;
	uint8_t *_code;
	ValueArray _constants;
};

#endif //LAX_CHUNK_H

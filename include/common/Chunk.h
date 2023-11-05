#ifndef LAX_CHUNK_H
#define LAX_CHUNK_H

#include <vector>

#include "values/Value.h"
#include "values/ValueArray.h"

/**
 * @brief Enumeration of opcodes.
 *
 * This enumeration represents the opcodes that can be used in the bytecode.
 * Each opcode represents an action to perform at runtime.
 */
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
    OP_RETURN
};

/**
 * @class Chunk
 * @brief Chunk of bytecode.
 *
 * This class represents a chunk of bytecode. A chunk is a sequence of codes that
 * can be executed by the virtual machine. The virtual machine interprets the
 * bytecode and executes the instructions.
 *
 * The bytecode is composed of instructions, represented as a sequence of codes.
 * An instruction is composed of an OpCode that specifies the action to
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
    /**
     * @brief Class constructor.
     *
     * Creates a new bytecode chunk.
     */
    Chunk();

    /**
     * @brief Class destructor.
     *
     * Frees the memory allocated for the bytecode.
     */
    ~Chunk();

    /**
     * @brief Writes an instruction in the bytecode of the chunk.
     * @param byte The instruction to write, represented as a byte.
     */
    void writeByte(uint8_t byte);

    /**
     * @brief Retrieves the opcode with the given offset.
     *
     * This function retrieves the opcode stored at the given offset. If no
     * offset is specified, the default offset of 0 is used.
     *
     * @param offset (optional) The offset value to lookup the opcode.
     * @return The opcode at the given offset.
     */
    uint8_t* getCode(int offset = 0);

    /**
     * @brief Adds a constant value in the constant pool of the chunk.
     * @param value The constant value to add.
     * @return The index of the new constant in the constant pool.
     */
    uint16_t addConstant(Value value);

    /**
     * @brief Retrieves a constant value from the constant pool.
     *
     * If no offset is provided, the default offset of 0 is used.
     *
     * @param offset (optional) The offset of the constant in the constant pool.
     * @return The constant value at the given offset.
     */
    const Value& getConstant(int offset = 0);

    /**
     * @brief Retrieves the number of codes in the chunk.
     * @return The number of codes.
     */
    uint16_t getCount() const;

    /**
     * @brief Retrieves the number of constants in the chunk.
     * @return The number of constants.
     */
    int getConstantCount() const;

private:
    uint16_t m_count;
    uint16_t m_capacity;
    uint8_t* m_code;
    ValueArray m_constants;
};

#endif //LAX_CHUNK_H

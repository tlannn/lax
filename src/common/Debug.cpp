#include "common/Debug.h"
#include "common/Chunk.h"
#include "objects/ObjFunction.h"
#include "utils/Logger.h"
#include "values/Value.h"

/**
 * @brief Disassembles a simple instruction containing only one byte.
 * @param name The name of the instruction.
 * @param offset The offset of the instruction in the chunk.
 * @return The offset of the next instruction.
 */
static int simpleInstruction(const char* name, int offset) {
    std::cout << name << std::endl;
    return offset + 1;
}

/**
 * @brief Disassembles a constant instruction.
 * @param name The name of the instruction.
 * @param chunk The chunk containing the instruction.
 * @param offset The offset of the instruction in the chunk.
 * @return The offset of the next instruction.
 */
static int constantInstruction(const std::string& name, Chunk* chunk, int offset) {
    uint8_t constant = *chunk->getCode(offset + 1);
    Value value = chunk->getConstant(constant);

    std::cout << name << " " << Value::toString(value) << std::endl;

    return offset + 2;
}

/**
 * @brief Disassembles an instruction containing only two bytes.
 * @param name The name of the instruction.
 * @param chunk The chunk containing the instruction.
 * @param offset The offset of the instruction in the chunk.
 * @return The offset of the next instruction.
 */
static int byteInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t slot = *chunk->getCode(offset + 1);
    std::cout << name << " " << std::setw(4) << std::setfill('0')
              << static_cast<int>(slot) << std::endl;
    return offset + 2;
}

/**
 * @brief Disassembles a jump instruction.
 * @param name The name of the instruction.
 * @param sign The sign of the jump ; `true` means forward jump in the bytecode,
 * and `false` backward jump.
 * @param chunk The chunk containing the instruction.
 * @param offset The offset of the instruction in the bytecode.
 * @return The offset of the next instruction in the bytecode.
 */
static int jumpInstruction(const char* name, bool sign, Chunk* chunk, int offset) {
    uint16_t jump = static_cast<uint16_t>(*chunk->getCode(offset + 1) << 8);
    jump |= *chunk->getCode(offset + 2);

    std::cout << name << " " << std::setw(4) << std::setfill('0')
              << static_cast<int>(offset) << " -> "
              << offset + 3 + sign * jump << std::endl;

    return offset + 3;
}

/**
 * @brief Disassembles a closure instruction.
 * @param name The name of the instruction.
 * @param chunk The chunk containing the instruction.
 * @param offset The offset of the instruction in the chunk.
 * @return The offset of the next instruction.
 */
static int closureInstruction(const char* name, Chunk* chunk, int offset) {
    ++offset;
    uint8_t constant = *chunk->getCode(offset++);
    std::cout << static_cast<int>(constant) << " " << name << " "
              << Value::toString(
                  const_cast<Value&>(chunk->getConstant(constant))
              )
              << std::endl;

    ObjFunction* function = AS_FUNCTION(chunk->getConstant(constant));

    for (int j = 0; j < function->getUpvalueCount(); ++j) {
        int isLocal = static_cast<int>(*chunk->getCode(offset++));
        int index = static_cast<int>(*chunk->getCode(offset++));
        std::cout << std::setw(4) << std::setfill('0') << offset - 2 << " | "
                  << (isLocal ? "local" : "upvalue") << " "
                  << index << std::endl;
    }
    return offset;
}

void disassembleChunk(Chunk* chunk, const std::string& name) {
    std::cout << "== " << name << " ==" << std::endl;

    // Disassemble all instructions in chunk
    for (int offset = 0; offset < chunk->getCount();) {
        offset = disassembleInstruction(chunk, offset);
    }
}

int disassembleInstruction(Chunk* chunk, int offset) {
    std::cout << std::setw(4) << std::setfill('0') << offset << " ";

    uint8_t instruction = *chunk->getCode(offset);

    switch (instruction) {
        case OpCode::OP_EXTENDED_ARG:
            return simpleInstruction("OP_EXTENDED_ARG", offset);
        case OpCode::OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OpCode::OP_NULL:
            return simpleInstruction("OP_NULL", offset);
        case OpCode::OP_TRUE:
            return simpleInstruction("OP_TRUE", offset);
        case OpCode::OP_FALSE:
            return simpleInstruction("OP_FALSE", offset);
        case OpCode::OP_POP:
            return simpleInstruction("OP_POP", offset);
        case OpCode::OP_DEFINE_GLOBAL:
            return constantInstruction("OP_DEFINE_GLOBAL", chunk, offset);
        case OpCode::OP_GET_GLOBAL:
            return constantInstruction("OP_GET_GLOBAL", chunk, offset);
        case OpCode::OP_SET_GLOBAL:
            return constantInstruction("OP_SET_GLOBAL", chunk, offset);
        case OpCode::OP_GET_UPVALUE:
            return byteInstruction("OP_GET_UPVALUE", chunk, offset);
        case OpCode::OP_SET_UPVALUE:
            return byteInstruction("OP_SET_UPVALUE", chunk, offset);
        case OpCode::OP_GET_LOCAL:
            return byteInstruction("OP_GET_LOCAL", chunk, offset);
        case OpCode::OP_SET_LOCAL:
            return byteInstruction("OP_SET_LOCAL", chunk, offset);
        case OpCode::OP_EQUAL:
            return simpleInstruction("OP_EQUAL", offset);
        case OpCode::OP_NOT_EQUAL:
            return simpleInstruction("OP_NOT_EQUAL", offset);
        case OpCode::OP_LESS:
            return simpleInstruction("OP_LESS", offset);
        case OpCode::OP_LESS_EQUAL:
            return simpleInstruction("OP_LESS_EQUAL", offset);
        case OpCode::OP_GREATER:
            return simpleInstruction("OP_GREATER", offset);
        case OpCode::OP_GREATER_EQUAL:
            return simpleInstruction("OP_GREATER_EQUAL", offset);
        case OpCode::OP_ADD:
            return simpleInstruction("OP_ADD", offset);
        case OpCode::OP_SUBTRACT:
            return simpleInstruction("OP_SUBTRACT", offset);
        case OpCode::OP_MULTIPLY:
            return simpleInstruction("OP_MULTIPLY", offset);
        case OpCode::OP_DIVIDE:
            return simpleInstruction("OP_DIVIDE", offset);
        case OpCode::OP_NOT:
            return simpleInstruction("OP_NOT", offset);
        case OpCode::OP_NEGATE:
            return simpleInstruction("OP_NEGATE", offset);
        case OpCode::OP_CALL:
            return byteInstruction("OP_CALL", chunk, offset);
        case OpCode::OP_CLOSE_UPVALUE:
            return simpleInstruction("OP_CLOSE_UPVALUE", offset);
        case OpCode::OP_CLOSURE:
            return closureInstruction("OP_CLOSURE", chunk, offset);
        case OpCode::OP_JUMP:
            return jumpInstruction("OP_JUMP", true, chunk, offset);
        case OpCode::OP_JUMP_FALSE:
            return jumpInstruction("OP_JUMP_FALSE", true, chunk, offset);
        case OpCode::OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            Logger::log("Unknown opcode " + std::to_string(instruction));
            return offset + 1;
    }
}

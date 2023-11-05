#ifndef LAX_DEBUG_H
#define LAX_DEBUG_H

#include <iomanip>
#include <iostream>
#include <string>

class Chunk;

/**
 * @brief Disassembles a chunk.
 *
 * This function prints a human-readable representation of the bytecode of a
 * chunk.
 *
 * @param chunk The chunk to disassemble.
 * @param name The name of the output representation.
 */
void disassembleChunk(Chunk* chunk, const std::string& name);

/**
 * @brief Disassembles an instruction of the bytecode.
 *
 * This function prints a human-readable representation of an instruction of the
 * bytecode.
 *
 * @param chunk The chunk containing the instruction.
 * @param offset The offset of the instruction in the chunk.
 * @return The offset of the next instruction.
 */
int disassembleInstruction(Chunk* chunk, int offset);

#endif //LAX_DEBUG_H

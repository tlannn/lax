#ifndef LAX_DEBUG_H
#define LAX_DEBUG_H

#include <iomanip>
#include <iostream>
#include <string>

class Chunk;

/**
 * Print a human readable representation of the bytecode of a chunk.
 *
 * @param chunk the chunk to disassemble.
 * @param name the name of the output representation.
 */
void disassembleChunk(Chunk* chunk, const std::string& name);

/**
 * Disassemble a bytecode instruction in a chunk.
 *
 * @param chunk the chunk containing the instruction.
 * @param offset the offset of the instruction in the chunk.
 * @return the offset of the next instruction.
 */
int disassembleInstruction(Chunk* chunk, int offset);

#endif //LAX_DEBUG_H

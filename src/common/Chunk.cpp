#include "common/Chunk.h"
#include "common/Memory.h"

/// Class constructor.
Chunk::Chunk() :
    m_count(0),
    m_capacity(0),
    m_code(nullptr) {}

/// Class destructor.
Chunk::~Chunk() {
    FREE_ARRAY(uint8_t, m_code, m_capacity);
}

/// Write a byte in the bytecode of the chunk.
void Chunk::writeByte(uint8_t byte) {
    if (m_capacity < m_count + 1) {
        uint16_t oldCapacity = m_capacity;
        m_capacity = GROW_CAPACITY(oldCapacity);
        m_code = GROW_ARRAY(uint8_t, m_code, oldCapacity, m_capacity);
    }

    m_code[m_count] = byte;
    ++m_count;
}

/// Getter for a code in the bytecode.
uint8_t* Chunk::getCode(int offset) {
    return m_code + offset;
}

/// Add a constant value in the constant pool of the chunk.
uint16_t Chunk::addConstant(Value value) {
    m_constants.writeValue(value);
    return m_constants.getCount() - 1;
}

/// Getter for a constant in the constant pool.
const Value& Chunk::getConstant(int offset) {
    return m_constants.getValue(offset);
}

/// Getter for the number of codes written in the bytecode.
uint16_t Chunk::getCount() const {
    return m_count;
}

/// Return the number of constants in the constant pool.
int Chunk::getConstantCount() const {
    return m_constants.getCount();
}

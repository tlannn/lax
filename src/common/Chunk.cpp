#include "common/Chunk.h"
#include "common/Memory.h"

Chunk::Chunk() :
    m_count(0),
    m_capacity(0),
    m_code(nullptr) {}

Chunk::~Chunk() {
    FREE_ARRAY(uint8_t, m_code, m_capacity);
}

void Chunk::writeByte(uint8_t byte) {
    if (m_capacity < m_count + 1) {
        uint16_t oldCapacity = m_capacity;
        m_capacity = GROW_CAPACITY(oldCapacity);
        m_code = GROW_ARRAY(uint8_t, m_code, oldCapacity, m_capacity);
    }

    m_code[m_count] = byte;
    ++m_count;
}

uint8_t* Chunk::getCode(int offset) {
    return m_code + offset;
}

uint16_t Chunk::addConstant(Value value) {
    m_constants.writeValue(value);
    return m_constants.getCount() - 1;
}

const Value& Chunk::getConstant(int offset) {
    return m_constants.getValue(offset);
}

uint16_t Chunk::getCount() const {
    return m_count;
}

int Chunk::getConstantCount() const {
    return m_constants.getCount();
}

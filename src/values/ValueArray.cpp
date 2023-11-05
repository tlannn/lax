#include "values/ValueArray.h"

ValueArray::ValueArray() :
    m_count(0),
    m_capacity(0),
    m_values(nullptr) {}

ValueArray::~ValueArray() {
    FREE_ARRAY(Value, m_values, m_capacity);
}

void ValueArray::writeValue(Value value) {
    if (m_capacity < m_count + 1) {
        int oldCapacity = m_capacity;
        m_capacity = GROW_CAPACITY(oldCapacity);
        m_values = GROW_ARRAY(Value, m_values, oldCapacity, m_capacity);
    }

    m_values[m_count] = value;
    ++m_count;
}

int ValueArray::getCount() const {
    return m_count;
}

const Value& ValueArray::getValue(int offset) {
    return m_values[offset];
}

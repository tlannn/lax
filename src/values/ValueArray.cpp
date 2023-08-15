#include "values/ValueArray.h"

/// Class constructor.
ValueArray::ValueArray() : _count(0), _capacity(0), _values(nullptr) {}

/// Class destructor.
ValueArray::~ValueArray() {
    FREE_ARRAY(Value, _values, _capacity);
}

/// Append a value to the array.
void ValueArray::writeValue(Value value) {
    if (_capacity < _count + 1) {
        int oldCapacity = _capacity;
        _capacity = GROW_CAPACITY(oldCapacity);
        _values = GROW_ARRAY(Value, _values, oldCapacity, _capacity);
    }

    _values[_count] = value;
    ++_count;
}

/// Getter for the number of values in the array.
int ValueArray::getCount() const {
    return _count;
}

/// Return a value from the array.
const Value& ValueArray::getValue(int offset) {
    return _values[offset];
}

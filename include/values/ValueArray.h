#ifndef LAX_VALUEARRAY_H
#define LAX_VALUEARRAY_H

#include "values/Value.h"

/**
 * @class ValueArray
 * @brief A dynamic array of Lax values.
 *
 * This class is used to store a dynamic array of Lax values.
 *
 * The array is implemented as a dynamic array, where the capacity of the array
 * is doubled when the number of values exceeds the capacity.
 *
 * The array is allocated on the heap.
 */
class ValueArray {
public:
    /**
     * @brief Class constructor.
     *
     * Initializes the array with a null array of values.
     */
    ValueArray();

    /**
     * @brief Class destructor.
     *
     * Frees the memory allocated for the array.
     */
    ~ValueArray();

    /**
     * @brief Appends a value to the array.
     *
     * If the number of values exceeds the capacity of the array, the array is
     * resized.
     *
     * @param value The value to add.
     */
    void writeValue(Value value);

    /**
     * @brief Retrieves the number of values in the array.
     * @return The number of values.
     */
    int getCount() const;

    /**
     * @brief Returns the value at a given offset in the array.
     *
     * This function returns the value at a given offset in the array.
     *
     * @param offset The offset of the value to retrieve.
     * @return The value at the given offset.
     * @throws std::out_of_range If the offset is out of range.
     */
    const Value& getValue(int offset);

private:
    int m_count;
    int m_capacity;
    Value* m_values;
};

#endif // LAX_VALUEARRAY_H

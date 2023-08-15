#ifndef LAX_VALUEARRAY_H
#define LAX_VALUEARRAY_H

#include "values/Value.h"

/**
 * Array of values.
 */
class ValueArray {
public:
    /// Class constructor.
    ValueArray();

    /// Class destructor.
    ~ValueArray();

    /**
     * Append a value to the array.
     * @param value the value to add.
     */
    void writeValue(Value value);

    /**
     * Getter for the number of values in the array.
     * @return the number of values.
     */
    int getCount() const;

    /**
     * Return a value from the array.
     * @param offset the offset of the value in the array.
     * @return the value.
     */
    const Value& getValue(int offset);

private:
    int _count;
    int _capacity;
    Value *_values;
};

#endif // LAX_VALUEARRAY_H

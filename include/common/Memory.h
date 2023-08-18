#ifndef LAX_MEMORY_H
#define LAX_MEMORY_H

#include <cstdlib>

#define ALLOCATE(type, count) \
    static_cast<type*>(reallocate(nullptr, 0, sizeof(type) * (count)))

#define FREE(type, pointer)         reallocate(pointer, sizeof(type), 0)

#define GROW_CAPACITY(capacity)     ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    static_cast<type*>(reallocate( \
        pointer, sizeof(type) * (oldCount),  sizeof(type) * (newCount) \
    ))

#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#endif //LAX_MEMORY_H

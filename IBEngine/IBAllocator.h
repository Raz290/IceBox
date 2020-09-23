#pragma once

#include "IBEngineAPI.h"

#include <stdint.h>
#include <utility>
#include <new>

namespace IB
{
    IB_API void *memoryAllocate(size_t size, size_t alignment);
    IB_API void memoryFree(void *memory);

    template <typename T, typename... TArgs>
    T *allocate(TArgs &&... args)
    {
        void *memory = memoryAllocate(sizeof(T), alignof(T));
        return new (memory) T(std::forward<TArgs>(args)...);
    }

    template <typename T>
    void deallocate(T *object)
    {
        object->~T();
        memoryFree(object);
    }
} // namespace IB

//
// Created by root on 1/2/24.
//

#ifndef GAMESERVER_ALLOCATOR_H
#define GAMESERVER_ALLOCATOR_H
#include "../Core/CoreHeader.h"

class BaseAllocator {
public:
    static void* Alloc(int32 size);
    static void Release(void* ptr);

};

class PoolAllocator
{
public:
    static void* Alloc(int32 size);
    static void Release(void* ptr);
};

template<typename T>
class StlAllocator
{
public:
    using value_type = T;

    StlAllocator() { }

    template<typename Other>
    StlAllocator(const StlAllocator<Other>&) { }

    T* allocate(size_t count)
    {
        const int32 size = static_cast<int32>(count * sizeof(T));
        return static_cast<T*>(PoolAllocator::Alloc(size));
    }

    void deallocate(T* ptr, size_t count)
    {
        PoolAllocator::Release(ptr);
    }

    template<typename U>
    bool operator==(const StlAllocator<U>&) { return true; }

    template<typename U>
    bool operator!=(const StlAllocator<U>&) { return false; }
};
#endif //GAMESERVER_ALLOCATOR_H

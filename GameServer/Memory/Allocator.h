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

template<typename Type,typename ...Args>
Type* xnew(Args&&...args)
{
    Type* memory = static_cast<Type*>(PoolAllocator::Alloc(sizeof(Type)));
    new(memory)Type(forward<Args>(args)...);
    return memory;
}

template<typename Type>
void xdelete(Type* obj)
{
    obj->~Type();
    PoolAllocator::Release(obj);
}
#endif //GAMESERVER_ALLOCATOR_H

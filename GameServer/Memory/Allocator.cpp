//
// Created by root on 1/2/24.
//

#include "Allocator.h"

void *BaseAllocator::Alloc(int32 size) {
    return ::malloc(size);
}

void BaseAllocator::Release(void *ptr) {
    ::free(ptr);
}


void *PoolAllocator::Alloc(int32 size) {
    return GMemory->Allocate(size);
}

void PoolAllocator::Release(void *ptr) {
    GMemory->Release(ptr);
}

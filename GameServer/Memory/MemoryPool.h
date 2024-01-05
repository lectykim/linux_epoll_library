//
// Created by user on 24. 1. 5.
//

#ifndef GAMESERVER_MEMORYPOOL_H
#define GAMESERVER_MEMORYPOOL_H
#include "../Core/CoreHeader.h"
struct MemoryHeader
{
    MemoryHeader(int32 size):allocSize(size){}

    static void* AttachHeader(MemoryHeader* header,int32 size)
    {
        new(header)MemoryHeader(size);
        return reinterpret_cast<void*>(++header);
    }

    static MemoryHeader* DetachHeader(void* ptr)
    {
        MemoryHeader* header = reinterpret_cast<MemoryHeader*>(ptr)-1;
        return header;
    }

    int32 allocSize;
};

class MemoryPool {
public:
    MemoryPool(int32 allocSize):_allocSize(allocSize){};
    ~MemoryPool();

    void Push(MemoryHeader* ptr);
    MemoryHeader* Pop();

private:
    USE_LOCK
    int32 _allocSize=0;
    queue<MemoryHeader*>_queue;
};


#endif //GAMESERVER_MEMORYPOOL_H

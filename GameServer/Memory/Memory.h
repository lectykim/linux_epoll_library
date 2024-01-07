//
// Created by user on 24. 1. 5.
//

#ifndef GAMESERVER_MEMORY_H
#define GAMESERVER_MEMORY_H
#include "../Core/CoreHeader.h"
class MemoryPool;

class Memory {
    enum
    {
        POOL_COUNT = (1024/32)+(1024/128)+(2048/256),
        MAX_ALLOC_SIZE=4096
    };

public:
    Memory();
    ~Memory();

    void* Allocate(int32 size);
    void Release(void* ptr);


private:
    vector<MemoryPool*>_pools;

    MemoryPool* _poolTable[MAX_ALLOC_SIZE+1];
};



#endif //GAMESERVER_MEMORY_H

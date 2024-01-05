//
// Created by user on 24. 1. 5.
//

#include "MemoryPool.h"

void MemoryPool::Push(MemoryHeader *ptr) {
    WRITE_LOCK;
    ptr->allocSize=0;
    _queue.push(ptr);
}

MemoryHeader *MemoryPool::Pop() {
    MemoryHeader* header = nullptr;
    {
        WRITE_LOCK;
        if(!_queue.empty())
        {
            header = _queue.front();
            _queue.pop();
        }
    }

    if(header == nullptr)
    {
        header = reinterpret_cast<MemoryHeader*>(::malloc(_allocSize));
    }
    else
    {
        ASSERT_CRASH(header->allocSize == 0);
    }
    return header;
}

MemoryPool::~MemoryPool() {
    while(!_queue.empty())
    {
        MemoryHeader* header = _queue.front();
        _queue.pop();
        ::free(header);
    }
}

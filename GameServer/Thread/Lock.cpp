//
// Created by root on 1/2/24.
//

#include "Lock.h"
#include "../Core/CoreHeader.h"
void Lock::WriteLock(const char *name) {
    // 동일한 쓰레드가 소유하고 있다면 무조건 성공.
    const uint32 lockThreadId = (_lockFlag.load() & WRITE_THREAD_MASK)>>16;
    if(LThreadId == lockThreadId)
    {
        _writeCount++;
        return;
    }

    // 아무도 소유 및 공유하고 있지 않을 때, 경합해서 소유권을 얻는다.
    const int64 beginTick = getTick();
    const uint32 desired = ((LThreadId<<16)& WRITE_THREAD_MASK);
    while(true)
    {
        for(uint32 spinCount = 0;spinCount < MAX_SPIN_COUNT;spinCount++)
        {
            uint32 expected = EMPTY_FLAG;
            if(_lockFlag.compare_exchange_strong(OUT expected,desired))
            {
                _writeCount++;
                return;
            }
        }

        // 여기에 진입했다면 문제가 있는 상황임. 데드락이거나,
        if(getTick()-beginTick >= ACQUIRE_TIMEOUT_TICK)
            exit(-1);

        this_thread::yield();
    }
}

void Lock::WriteUnlock(const char *name) {

    //ReadLock 다 풀기 전에는 WriteUnlock 불가능.
    if((_lockFlag.load() & READ_COUNT_MASK)!=0)
        exit(-1);

    const int32 lockCount = --_writeCount;
    if(lockCount==0)
        _lockFlag.store(EMPTY_FLAG);
}

void Lock::ReadLock(const char *name) {
    const uint32 lockThreadId = (_lockFlag.load()&WRITE_THREAD_MASK)>>16;
    // 동일한 쓰레드가 소유하고 있다면 무조건 성공.
    if(LThreadId == lockThreadId)
    {
        _lockFlag.fetch_add(1);
        return;
    }

    // 아무도 소유하고 있지 않을 때, 경합해서 공유 카운트를 올린다.
    const int64 beginTick = getTick();
    while(true)
    {
        for(uint32 spinCount=0;spinCount<MAX_SPIN_COUNT;spinCount++) {
            uint32 expected = (_lockFlag.load() & READ_COUNT_MASK);
            if (_lockFlag.compare_exchange_strong(OUT expected, expected + 1))
                return;
        }

        if(getTick()-beginTick >= ACQUIRE_TIMEOUT_TICK)
            exit(-1);

        this_thread::yield();
    }
}

void Lock::ReadUnlock(const char *name) {
    if((_lockFlag.fetch_sub(1)&READ_COUNT_MASK)==0)
        exit(-1);
}

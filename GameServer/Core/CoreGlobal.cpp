//
// Created by root on 1/2/24.
//

#include "CoreGlobal.h"
#include "../Thread/ThreadManager.h"
#include "../Network/EpollManager.h"

ThreadManager* GThreadManager = nullptr;
EpollManager* GEpollManager = nullptr;
SendBufferManager* GSendBufferManager = nullptr;
JobQueue* GJobQueue = nullptr;
Memory* GMemory = nullptr;
class CoreGlobal
{
public:
    CoreGlobal()
    {
        GThreadManager = new ThreadManager();
        GEpollManager = new EpollManager();
        GMemory = new Memory();
        GSendBufferManager = new SendBufferManager();
        GJobQueue = new JobQueue();
        GEpollManager->EpollInit();
    }

    ~CoreGlobal()
    {
        delete GThreadManager;
        delete GEpollManager;
        delete GSendBufferManager;
        delete GJobQueue;
        delete GMemory;
    }
};

CoreGlobal* GCoreGlobal = new CoreGlobal();
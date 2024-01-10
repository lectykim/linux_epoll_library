//
// Created by root on 1/2/24.
//

#include "CoreGlobal.h"
#include "../Thread/ThreadManager.h"
#include "../Network/EpollManager.h"
#include "../Content/ClientPacketHandler.h"
#include "../Job/PacketQueue.h"
ThreadManager* GThreadManager = nullptr;
EpollManager* GEpollManager = nullptr;
SendBufferManager* GSendBufferManager = nullptr;
PacketQueue* GPacketQueue = nullptr;
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
        GPacketQueue = new PacketQueue();
        GEpollManager->EpollInit();
    }

    ~CoreGlobal()
    {
        delete GThreadManager;
        delete GEpollManager;
        delete GSendBufferManager;
        delete GMemory;
        delete GPacketQueue;
    }
};

CoreGlobal* GCoreGlobal = new CoreGlobal();
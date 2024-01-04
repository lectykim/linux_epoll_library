//
// Created by root on 1/2/24.
//

#include "CoreGlobal.h"
#include "../Thread/ThreadManager.h"
#include "../Network/EpollManager.h"

ThreadManager* GThreadManager = nullptr;
EpollManager* GEpollManager = nullptr;
class CoreGlobal
{
public:
    CoreGlobal()
    {
        GThreadManager = new ThreadManager();
        GEpollManager = new EpollManager();
        GEpollManager->EpollInit();
    }

    ~CoreGlobal()
    {
        delete GThreadManager;
        delete GEpollManager;
    }
};

CoreGlobal* GCoreGlobal = new CoreGlobal();
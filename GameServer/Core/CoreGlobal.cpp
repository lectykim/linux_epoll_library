//
// Created by root on 1/2/24.
//

#include "CoreGlobal.h"
#include "../Thread/ThreadManager.h"

ThreadManager* GThreadManager = nullptr;

class CoreGlobal
{
public:
    CoreGlobal()
    {
        GThreadManager = new ThreadManager();
    }

    ~CoreGlobal()
    {
        delete GThreadManager;
    }
};

CoreGlobal* GCoreGlobal = new CoreGlobal();
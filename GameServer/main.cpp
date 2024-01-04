#include <iostream>
#include "Core/CoreHeader.h"
#include "Thread/ThreadManager.h"
#include "Core/CoreGlobal.h"
#include "Thread/Lock.h"
#include "Util/LockQueue.h"
#include "Network/SocketManager.h"
#include "Network/EpollManager.h"
SimpleLockQueue<int32> simpleLockQueue;
int main() {
    int32 server_fd = SocketManager::Init();
    GEpollManager->EpollAdd(server_fd);
    GThreadManager->Launch([](){

        GEpollManager->EpollRunning();
    });


    GThreadManager->Join();
    return 0;
}

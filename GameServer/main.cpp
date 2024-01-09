#include <iostream>
#include "Core/CoreHeader.h"
#include "Thread/ThreadManager.h"
#include "Core/CoreGlobal.h"
#include "Thread/Lock.h"
#include "Conetent/ClientPacketHandler.h"
#include "Network/SocketManager.h"
#include "Network/EpollManager.h"
void DoWorkerJob()
{
    while(true)
    {
        GJobQueue->Execute();
    }
}
int main() {
    ClientPacketHandler::Init();

    int32 server_fd = SocketManager::Init();
    GEpollManager->EpollAdd(server_fd);
    GThreadManager->Launch([](){

        GEpollManager->EpollRunning();
    });
    for(int32 i=0;i<5;i++)
    {
        GThreadManager->Launch([](){
            DoWorkerJob();
        });
    }

    GThreadManager->Join();
    return 0;
}

#include <iostream>
#include "Core/CoreHeader.h"
#include "Thread/ThreadManager.h"
#include "Core/CoreGlobal.h"
#include "Thread/Lock.h"
#include "Content/ClientPacketHandler.h"
#include "Network/SocketManager.h"
#include "Network/EpollManager.h"
#include "Job/PacketQueue.h"
void DoWorkerJob()
{
    while(true)
    {
        GPacketQueue->Execute();
        this_thread::sleep_for(10ms);
    }
}
int main() {
    ClientPacketHandler::Init();

    int32 server_fd = SocketManager::Init();
    GEpollManager->EpollAdd(server_fd);
    GThreadManager->Launch([](){

        GEpollManager->EpollRunning();
    });
    GThreadManager->Launch([](){
        DoWorkerJob();
    });

    GThreadManager->Join();
    return 0;
}

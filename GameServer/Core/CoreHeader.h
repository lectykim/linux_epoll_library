//
// Created by root on 1/2/24.
//

#ifndef GAMESERVER_COREHEADER_H
#define GAMESERVER_COREHEADER_H

using namespace std;


#include "Types.h"
#include <memory>
#include <iostream>
#include "CoreGlobal.h"
#include <vector>
#include <unistd.h>
#include <ctime>
#include "CoreMacro.h"
#include <thread>
#include <queue>
#include <cstring>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include "../Thread/Lock.h"
#include "../Network/SendBuffer.h"
#include <functional>
#include "../Job/Job.h"
#include "../Util/LockQueue.h"
#include "../Job/JobQueue.h"
#include "../Network/SendBuffer.h"
#include "../Network/RecvBuffer.h"
#include "CoreTLS.h"
#include "../Memory/Memory.h"
#include "../Memory/MemoryPool.h"

static int64 getTick()
{
    struct timespec ts{};
    int64 theTick;
    clock_gettime(CLOCK_REALTIME,&ts);
    theTick = ts.tv_nsec/1000000;
    theTick += ts.tv_sec*1000;
    return theTick;
}
using CallBackType = std::function<void()>;
#endif //GAMESERVER_COREHEADER_H

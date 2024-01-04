//
// Created by root on 1/2/24.
//

#ifndef GAMESERVER_COREHEADER_H
#define GAMESERVER_COREHEADER_H

#include "Types.h"
#include <iostream>
#include "CoreTLS.h"
#include "CoreGlobal.h"
#include <vector>
#include <unistd.h>
#include <ctime>
#include "CoreMacro.h"
#include <thread>
#include <queue>
#include "../Memory/Container.h"
#include <cstring>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
using namespace std;

static int64 getTick()
{
    struct timespec ts{};
    int64 theTick;
    clock_gettime(CLOCK_REALTIME,&ts);
    theTick = ts.tv_nsec/1000000;
    theTick += ts.tv_sec*1000;
    return theTick;
}

#endif //GAMESERVER_COREHEADER_H

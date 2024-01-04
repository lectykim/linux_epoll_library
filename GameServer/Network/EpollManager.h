//
// Created by user on 24. 1. 4.
//

#ifndef GAMESERVER_EPOLLMANAGER_H
#define GAMESERVER_EPOLLMANAGER_H
#include "../Core/CoreHeader.h"

enum {
    MAX_EVENTS=1024
};

class EpollManager {


public:
    int32 EpollInit();
    int32 EpollAdd(int32 fd);
    void EpollRunning();
private:
    int32 _fdEpoll=-1;
    bool _isEpollInit=false;
    struct epoll_event _events[MAX_EVENTS];
    int32 _eventCount,_timeout=-1;
    int32 _socketFd;
};


#endif //GAMESERVER_EPOLLMANAGER_H

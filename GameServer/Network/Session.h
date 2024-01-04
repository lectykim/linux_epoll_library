//
// Created by user on 24. 1. 4.
//

#ifndef GAMESERVER_SESSION_H
#define GAMESERVER_SESSION_H

#include "../Core/CoreHeader.h"

class Session {


private:
    int32 _fd;
    sockaddr_in _address;

private:
    Lock _lock;
};


#endif //GAMESERVER_SESSION_H

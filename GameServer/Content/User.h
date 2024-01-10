//
// Created by user on 24. 1. 10.
//

#ifndef GAMESERVER_USER_H
#define GAMESERVER_USER_H

#include "../Core/CoreHeader.h"
#include "../Protocol/Protocol.pb.h"
#include "../Protocol/Enum.pb.h"
class User {
public:
    uint64 userSeq;
    string name;
    Protocol::PlayerType type = Protocol::PLAYER_NONE_MASTER;
    weak_ptr<GameSession> ownerSession;
};


#endif //GAMESERVER_USER_H

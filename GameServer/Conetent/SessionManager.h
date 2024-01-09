//
// Created by user on 24. 1. 8.
//

#ifndef GAMESERVER_SESSIONMANAGER_H
#define GAMESERVER_SESSIONMANAGER_H
#include "../Core/CoreHeader.h"
class GameSession;

using GameSessionRef = shared_ptr<GameSession>;

class SessionManager {
public:
    void Add(int32 fd,const GameSessionRef& session);
    void Remove(int32 fd);
    void Broadcast(const SendBufferRef& sendBuffer);
    GameSessionRef find(int32 fd);

private:
    USE_LOCK;
    map<int32,GameSessionRef> _sessions;
};

extern SessionManager GSessionManager;
#endif //GAMESERVER_SESSIONMANAGER_H

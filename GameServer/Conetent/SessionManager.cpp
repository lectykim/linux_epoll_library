//
// Created by user on 24. 1. 8.
//

#include "SessionManager.h"

SessionManager GSessionManager;

void SessionManager::Add(int32 fd,const GameSessionRef& session) {
    WRITE_LOCK;
    _sessions.insert({fd,session});
}

void SessionManager::Remove(int32 fd) {
    WRITE_LOCK;
    _sessions.erase(fd);
}

void SessionManager::Broadcast(const SendBufferRef& sendBuffer) {
    WRITE_LOCK;
    auto it = _sessions.begin();
    for(it;it != _sessions.end();it++)
    {
        //it->second->Send(sendBuffer);
    }
}

GameSessionRef SessionManager::find(int32 fd) {
    return _sessions.find(fd)->second;
}



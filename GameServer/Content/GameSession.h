//
// Created by user on 24. 1. 8.
//

#ifndef GAMESERVER_GAMESESSION_H
#define GAMESERVER_GAMESESSION_H
#include "../Core/CoreHeader.h"
#include "../Network/Session.h"
class GameSession :public PacketSession{
public:
    ~GameSession()
    {
        cout << "~GameSession" << endl;
    }

    virtual void OnConnected() override;
    virtual void OnDisconnected() override;
    virtual void OnRecvPacket(BYTE* buffer,int32 len) override;
    virtual void OnSend(int32 len) override;
public:
    UserRef _user;
    weak_ptr<class Room> _room;
};


#endif //GAMESERVER_GAMESESSION_H

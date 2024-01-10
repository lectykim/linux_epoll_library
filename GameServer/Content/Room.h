//
// Created by user on 24. 1. 10.
//

#ifndef GAMESERVER_ROOM_H
#define GAMESERVER_ROOM_H
#include "../Core/CoreHeader.h"

class Room {
public:
    void Enter(const UserRef& user);
    void Leave(const UserRef& user);
    void Broadcast(const SendBufferRef& sendBuffer);

public:
    map<uint64,UserRef> _users;
    uint64 roomId;
    string roomName;
    uint64 masterId;
    string pw;
};

extern shared_ptr<Room> GRoom;
extern map<uint64,RoomRef>* GRoomMap;


#endif //GAMESERVER_ROOM_H

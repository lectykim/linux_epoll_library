//
// Created by user on 24. 1. 10.
//

#include "Room.h"
#include "User.h"
#include "../Network/Session.h"
#include "GameSession.h"
shared_ptr<Room> GRoom = make_shared<Room>();
map<uint64,RoomRef>* GRoomMap = new map<uint64,RoomRef>();
void Room::Enter(const UserRef& user) {
    _users[user->userSeq]=user;
}

void Room::Leave(const UserRef& user) {
    _users.erase(user->userSeq);
}

void Room::Broadcast(const SendBufferRef& sendBuffer) {
    for(auto& p : _users)
    {
        p.second->ownerSession.lock()->Send(sendBuffer);
    }
}

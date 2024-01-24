//
// Created by user on 24. 1. 8.
//

#include "GameSession.h"
#include "ClientPacketHandler.h"
#include "Room.h"
#include "../Job/PacketQueue.h"
void GameSession::OnConnected() {

}

void GameSession::OnDisconnected() {
    if(_user)
    {
        if(auto room = _room.lock())
        {
            room->Leave(_user);
        }
    }
}

void GameSession::OnRecvPacket(BYTE *buffer, int32 len) {
    PacketSessionRef session = GetPacketSessionRef();
    PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

    cout << "Packet Received" << endl;

    PacketItem* packetItem = new PacketItem();
    packetItem->packetSession = session;
    packetItem->buffer=buffer;
    packetItem->len=len;
    GPacketQueue->DoAsync(packetItem);
    //ClientPacketHandler::HandlePacket(session,buffer,len);
}

void GameSession::OnSend(int32 len) {
    //Session::OnSend(len);
}

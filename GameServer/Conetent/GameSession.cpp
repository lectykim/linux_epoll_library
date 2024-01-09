//
// Created by user on 24. 1. 8.
//

#include "GameSession.h"
#include "ClientPacketHandler.h"
void GameSession::OnConnected() {

}

void GameSession::OnDisconnected() {
    //Session::OnDisconnected();
}

void GameSession::OnRecvPacket(BYTE *buffer, int32 len) {
    PacketSessionRef session = GetPacketSessionRef();
    PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

    cout << "Packet Received" << endl;


    //PacketSession::OnRecvPacket(buffer, len);
    ClientPacketHandler::HandlePacket(session,buffer,len);
}

void GameSession::OnSend(int32 len) {
    //Session::OnSend(len);
}

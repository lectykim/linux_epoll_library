//
// Created by user on 24. 1. 4.
//

#include "Session.h"

string Session::GetAddress() {
    char addr[100];
    inet_ntop(AF_INET,(struct sockaddr_in*)&_address.sin_addr,addr,sizeof(addr));
    return addr;
}

int32 PacketSession::OnRecv(BYTE *buffer, int32 len) {
    int32 processLen = 0;

    while(true)
    {
        int32 dataSize = len - processLen;

        if(dataSize < sizeof(PacketHeader))
            break;

        PacketHeader header = *(reinterpret_cast<PacketHeader*>(&buffer[processLen]));

        //if(dataSize<header.size)
        //    break;

        OnRecvPacket(&buffer[processLen],header.size);
        processLen+=header.size;
    }
    return processLen;
}

PacketSession::PacketSession() {

}
PacketSession::~PacketSession()
{

}
Session::~Session()
{

}
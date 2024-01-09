//
// Created by user on 24. 1. 8.
//

#include "ClientPacketHandler.h"
PacketHandlerFunc GPacketHandler[UINT16_MAX];
bool Handle_INVALID(PacketSessionRef& session,BYTE* buffer,int32 len)
{

    cout << "Invalid call"<<endl;
    return false;
}

bool Handle_C_SIGNUP(PacketSessionRef& session,Protocol::C_SIGNUP& pkt)
{
    cout << "SignUp call"<<endl;
    return false;
}
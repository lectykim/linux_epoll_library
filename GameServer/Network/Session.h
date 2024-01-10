//
// Created by user on 24. 1. 4.
//

#ifndef GAMESERVER_SESSION_H
#define GAMESERVER_SESSION_H

#include "../Core/CoreHeader.h"
#include "RecvBuffer.h"
#include "SendBuffer.h"
enum class EventType : uint8{
        Connect,
        Disconnect,
        Recv,
        Send
};

struct PacketHeader
{
    uint16 size;
    uint16 id;
};

class Session :public enable_shared_from_this<Session>{

    enum {
        BUFFER_SIZE = 0x10000, //64MB
    };

public:
    Session(): _recvBuffer(BUFFER_SIZE){};
    virtual ~Session();

public:

    void Send(SendBufferRef sendBuffer);
    string GetAddress();
    int32 GetFd(){return _fd;}
    shared_ptr<Session> GetSessionRef(){return static_pointer_cast<Session>(shared_from_this());}

    virtual void OnConnected(){};
    virtual void OnSend(int32 len){}
    virtual void OnDisconnected(){};

public:
    int32 _fd;
    sockaddr_in _address;

private:
    Lock _lock;
public:
    RecvBuffer _recvBuffer;

};

class PacketSession:public Session{
public:
    PacketSession();
    virtual ~PacketSession();
    PacketSessionRef GetPacketSessionRef(){return static_pointer_cast<PacketSession>(shared_from_this());}

    int32 OnRecv(BYTE* buffer,int32 len);

protected:
    virtual void OnRecvPacket(BYTE* buffer,int32 len)=0;
};
#endif //GAMESERVER_SESSION_H

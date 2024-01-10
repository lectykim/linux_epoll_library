//
// Created by user on 24. 1. 9.
//

#ifndef GAMESERVER_PACKETQUEUE_H
#define GAMESERVER_PACKETQUEUE_H
#include <utility>

#include "../Core/CoreHeader.h"

struct PacketItem
{
    PacketSessionRef packetSession;
    BYTE* buffer;
    int32 len;
};

class PacketQueue {
public:
    void DoAsync(PacketItem* packetItem)
    {
        Push(packetItem);
    }

public:
    void Push(PacketItem* packetItem);
    void Execute();

private:
    SimpleLockQueue<PacketItem*> _queue;
    Atomic<int32> _packetCount;
};


#endif //GAMESERVER_PACKETQUEUE_H

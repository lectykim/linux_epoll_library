//
// Created by user on 24. 1. 9.
//

#include "PacketQueue.h"
#include "../Content/ClientPacketHandler.h"

void PacketQueue::Push(PacketItem* packetItem) {
   const int32 prevCount= _packetCount.fetch_add(1);
    _queue.Push(packetItem);
}

void PacketQueue::Execute() {
    if(_packetCount == 0)
    {
        return;
    }

    while(true)
    {
        vector<PacketItem*> items;
        _queue.PopAll(OUT items);

        for(int32 i=0;i<_packetCount;i++)
        {
            ClientPacketHandler::HandlePacket(items[i]->packetSession,items[i]->buffer,items[i]->len);
            delete items[i];
        }


        if(_packetCount.fetch_sub(_packetCount)==_packetCount)
            return;
    }
}
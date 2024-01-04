//
// Created by root on 1/2/24.
//

#ifndef GAMESERVER_CORETLS_H
#define GAMESERVER_CORETLS_H

#include "Types.h"
#include "CoreHeader.h"
extern thread_local uint32 LThreadId;
extern thread_local uint64 LEndTickCount;
extern thread_local shared_ptr<SendBufferChunk> LSendBufferChunk;

#endif //GAMESERVER_CORETLS_H

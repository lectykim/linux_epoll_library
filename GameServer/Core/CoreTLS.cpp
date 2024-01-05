//
// Created by root on 1/2/24.
//

#include "CoreTLS.h"
thread_local uint32 LThreadId=0;
thread_local uint64 LEndTickCount=0;
thread_local shared_ptr<SendBufferChunk> LSendBufferChunk;
thread_local JobQueue* LCurrentJobQueue;
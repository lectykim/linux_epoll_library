//
// Created by user on 24. 1. 4.
//

#include "SendBuffer.h"

void SendBuffer::Close(uint32 writeSize) {

    _writeSize = writeSize;
    _owner->Close(writeSize);
}


void SendBufferChunk::Reset() {
    _open = false;
    _usedSize = 0;
}

shared_ptr<SendBuffer> SendBufferChunk::Open(uint32 allocSize) {
    if(allocSize>SEND_BUFFER_CHUNK_SIZE)
        exit(-1);

    if(allocSize>FreeSize())
        return nullptr;

    _open = true;
    return make_shared<SendBuffer>(shared_from_this(),Buffer(),allocSize);
}

void SendBufferChunk::Close(uint32 writeSize) {
    _open = false;
    _usedSize += writeSize;
}

shared_ptr<SendBuffer> SendBufferManager::Open(uint32 size) {

    if(LSendBufferChunk == nullptr)
    {
        LSendBufferChunk = Pop();
        LSendBufferChunk->Reset();
    }

    //다 썼으면 새 것으로 교체
    if(LSendBufferChunk->FreeSize()<size)
    {
        LSendBufferChunk = Pop();
        LSendBufferChunk->Reset();
    }

    return LSendBufferChunk->Open(size);
}

shared_ptr<SendBufferChunk> SendBufferManager::Pop() {
    {
        WriteLockGuard writeLockGuard(_lock,typeid(this).name());

        if(!_sendBufferChunks.empty())
        {
            shared_ptr<SendBufferChunk> sendBufferChunk = _sendBufferChunks.back();
            _sendBufferChunks.pop_back();
            return sendBufferChunk;
        }
    }
    return {new SendBufferChunk, PushGlobal};
}

void SendBufferManager::Push(const shared_ptr<SendBufferChunk>& buffer) {
    WriteLockGuard writeLockGuard(_lock,typeid(this).name());
    _sendBufferChunks.push_back(buffer);
}

void SendBufferManager::PushGlobal(SendBufferChunk *buffer) {
    GSendBufferManager->Push(shared_ptr<SendBufferChunk>(buffer, PushGlobal));
}



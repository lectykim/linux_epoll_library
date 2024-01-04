//
// Created by user on 24. 1. 4.
//

#ifndef GAMESERVER_SENDBUFFER_H
#define GAMESERVER_SENDBUFFER_H
#include <utility>

#include "../Core/CoreHeader.h"

class SendBufferChunk;

class SendBuffer {
public:
    SendBuffer(shared_ptr<SendBufferChunk> owner,BYTE* buffer, uint32 allocSize)
    :_owner(std::move(owner)),_buffer(buffer),_allocSize(allocSize){};
    ~SendBuffer() = default;

    BYTE* Buffer(){return _buffer;}
    uint32 AllocSize(){return _allocSize;}
    uint32 WriteSize(){return _writeSize;}
    void Close(uint32 writeSize);

private:
    BYTE* _buffer;
    uint32 _allocSize=0;
    uint32 _writeSize=0;
    shared_ptr<SendBufferChunk> _owner;
};

class SendBufferChunk : public enable_shared_from_this<SendBufferChunk>
{
    enum
    {
        SEND_BUFFER_CHUNK_SIZE = 6000
    };

public:
    SendBufferChunk() = default;
    ~SendBufferChunk()=default;

    void Reset();
    shared_ptr<SendBuffer> Open(uint32 allocSize);
    void Close(uint32 writeSize);

    bool IsOpen(){return _open;}
    BYTE* Buffer(){return &_buffer[_usedSize];}
    uint32 FreeSize(){return static_cast<uint32>(_buffer.size())-_usedSize;}

private:
    Array<BYTE,SEND_BUFFER_CHUNK_SIZE> _buffer={};
    bool _open = false;
    uint32 _usedSize=0;
};

class SendBufferManager
{
public:
    shared_ptr<SendBuffer> Open(uint32 size);

private:
    shared_ptr<SendBufferChunk> Pop();
    void Push(const shared_ptr<SendBufferChunk>& buffer);

    static void PushGlobal(SendBufferChunk* buffer);

private:
    Lock _lock;
    Vector<shared_ptr<SendBufferChunk>> _sendBufferChunks;
};

#endif //GAMESERVER_SENDBUFFER_H

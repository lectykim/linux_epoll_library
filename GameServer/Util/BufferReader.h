//
// Created by root on 1/3/24.
//

#ifndef GAMESERVER_BUFFERREADER_H
#define GAMESERVER_BUFFERREADER_H
#include "../Core/CoreHeader.h"

class BufferReader {
public:
    BufferReader() = default;
    BufferReader(BYTE* buffer,uint32 size,uint32 pos=0)
    :_buffer(buffer),_size(size),_pos(pos){}
    ~BufferReader() = default;

    BYTE* Buffer(){return _buffer;}
    uint32 Size() {return _size;}
    uint32 ReadSize(){return _pos;}
    uint32 FreeSize(){return _size-_pos;}

    template<typename T>
    bool Peek(T* dest){return Peek(dest,sizeof(T));}
    bool Peek(void* dest,uint32 len);

    template<typename T>
    bool Read(T* dest){return Read(dest,sizeof(T));}
    bool Read(void* dest,uint32 len);
private:
    BYTE* _buffer = nullptr;
    uint32 _size = 0;
    uint32 _pos=0;
};


#endif //GAMESERVER_BUFFERREADER_H

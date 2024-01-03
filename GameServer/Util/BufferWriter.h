//
// Created by root on 1/3/24.
//

#ifndef GAMESERVER_BUFFERWRITER_H
#define GAMESERVER_BUFFERWRITER_H
#include "../Core/CoreHeader.h"

class BufferWriter {
    BufferWriter()=default;
    BufferWriter(BYTE* buffer,uint32 size,uint32 pos=0)
    :_buffer(buffer),_size(size),_pos(pos){};
    ~BufferWriter() = default;

    BYTE*			Buffer() { return _buffer; }
    uint32			Size() { return _size; }
    uint32			WriteSize() { return _pos; }
    uint32			FreeSize() { return _size - _pos; }

    template<typename T>
    bool Write(T* src){return Write(src,sizeof(T));}
    bool Write(void* src,uint32 len);

    template<typename T>
    T* Reserve(uint16 count=1);

private:
    BYTE* _buffer=  nullptr;
    uint32 _size=0;
    uint32 _pos=0;
};

template<typename T>
T *BufferWriter::Reserve(uint16 count) {
    if(FreeSize()<(sizeof(T)*count))
        return nullptr;

    T* ret = reinterpret_cast<T*>(&_buffer[_pos]);
    _pos += (sizeof(T)*count);
    return ret;
}


#endif //GAMESERVER_BUFFERWRITER_H

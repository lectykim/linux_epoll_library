//
// Created by root on 1/3/24.
//


#include "BufferReader.h"
#include "../Core/CoreHeader.h"
bool BufferReader::Peek(void *dest, uint32 len) {
    if(FreeSize()<len)
        return false;

    memcpy(dest,&_buffer[_pos],len);
    return true;
}

bool BufferReader::Read(void *dest, uint32 len) {
    if(!Peek(dest, len))
        return false;

    _pos += len;
    return true;
}

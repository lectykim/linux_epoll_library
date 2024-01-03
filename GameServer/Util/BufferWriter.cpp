//
// Created by root on 1/3/24.
//

#include "BufferWriter.h"
#include "../Core/CoreHeader.h"

bool BufferWriter::Write(void *src, uint32 len) {
    if(FreeSize()<len)
        return false;

    memcpy(&_buffer[_pos],src,len);
    _pos+=len;
    return true;

}

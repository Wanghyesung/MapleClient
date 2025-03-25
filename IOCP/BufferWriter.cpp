#include "pch.h"
#include "BufferWriter.h"

BufferWriter::BufferWriter(BYTE* _buffer, int _iBufferSize):
    m_iBufferSize(_iBufferSize),
    m_writeBuffer(_buffer),
    m_iWritePos(0)
{
}

BufferWriter::~BufferWriter()
{
}

bool BufferWriter::Write(void* _src, int _iLen)
{
    if(FreeSize() < _iLen)
        return false;

    memcpy(&m_writeBuffer[m_iWritePos], _src, _iLen);
    m_iWritePos += _iLen;
    return true;
}

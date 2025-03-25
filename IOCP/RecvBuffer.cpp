#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(int _iBufferSize):
    m_iReadPos(0),
    m_iWritePos(0),
    m_iBufferSize(_iBufferSize)
{
    m_iCapacity = m_iBufferSize * 1.2;
    m_vecRecvBuffer.resize(m_iCapacity);
}

RecvBuffer::~RecvBuffer()
{

}


bool RecvBuffer::Clear()
{
    int iDataSize = DataSize();

    if (iDataSize == 0)
    {
        m_iReadPos = 0;
        m_iWritePos = 0;
    }

    else
    {
        //용량이 버퍼 크기 보다 작아졌을 때
        if (FreeSize() < m_iBufferSize)
        {
            //r, w 맨 앞으로 밀기
            memcpy(&m_vecRecvBuffer[0], &m_vecRecvBuffer[m_iReadPos], iDataSize);
            
            m_iReadPos = 0;
            m_iWritePos = iDataSize;
        }
    }
    return false;
}

bool RecvBuffer::Read(int _iNumOfBytes)
{
    if (_iNumOfBytes > DataSize())
        return false;

    m_iReadPos += _iNumOfBytes;

    return true;
}

bool RecvBuffer::Write(int _iNumOfBytes)
{
    if (_iNumOfBytes > FreeSize())
        return false;

    m_iWritePos += _iNumOfBytes;

    return true;
}


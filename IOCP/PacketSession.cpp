#include "pch.h"
#include "PacketSession.h"

PacketSession::PacketSession()
{
}

PacketSession::~PacketSession()
{
}

int PacketSession::OnRecv(BYTE* _buffer, int _iLen)
{
    //_iLen 들어온 전체 크기
    int iProcessLen = 0;

    while (true)
    {
        int iDataSize = _iLen - iProcessLen;
        if (iDataSize < sizeof(PacketHeader))
            break;

        PacketHeader* pHeader = reinterpret_cast<PacketHeader*>(&_buffer[iProcessLen]);
        if (iDataSize < pHeader->size)
            break;

        OnRecvPacket(&_buffer[iProcessLen], pHeader->size);

        iProcessLen += pHeader->size;
    }


    return iProcessLen;
}

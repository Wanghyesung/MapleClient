#pragma once
#include "PacketSession.h"

class ServerSession : public PacketSession
{
public:
    ServerSession();
    virtual ~ServerSession();

    virtual void OnConnected();
    virtual int OnRecvPacket(BYTE* buffer, int len);
    virtual void OnSend(int len);
    virtual void OnDisConnected();

private:


};


#include "pch.h"
#include "IOCPEvent.h"

IOCPEvent::IOCPEvent(eIocpEvent _eType):
	m_eEventType(_eType)
{
}

IOCPEvent::~IOCPEvent()
{
	m_pOwner = nullptr;
}

void IOCPEvent::init()
{
	//운영체제가 접근하는 영역
	OVERLAPPED::hEvent = 0;
	OVERLAPPED::Internal = 0;
	OVERLAPPED::InternalHigh = 0;
	OVERLAPPED::Offset = 0;
	OVERLAPPED::OffsetHigh = 0;
}



IOCPSendEvent::IOCPSendEvent() :
	IOCPEvent(eIocpEvent::Send)
{
}

IOCPSendEvent::~IOCPSendEvent()
{
}





IOCPRecvEvent::IOCPRecvEvent() :
	IOCPEvent(eIocpEvent::Recv)
{
}

IOCPRecvEvent::~IOCPRecvEvent()
{
}




IOCPConnectEvent::IOCPConnectEvent() :
	IOCPEvent(eIocpEvent::Connect)
{
}

IOCPConnectEvent::~IOCPConnectEvent()
{
}



ICOPDisConnectEvent::ICOPDisConnectEvent() :
	IOCPEvent(eIocpEvent::DisConnect)
{
}

ICOPDisConnectEvent::~ICOPDisConnectEvent()
{
}

IOCPAcceptEvent::IOCPAcceptEvent() :
	IOCPEvent(eIocpEvent::Accept)
{
}

IOCPAcceptEvent::~IOCPAcceptEvent()
{
}

#include "pch.h"
#include "IOCP.h"
#include "Session.h"
#include "IOCPEvent.h"
#include "GThread.h"

IOCP::IOCP()
{
	m_IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
}

IOCP::~IOCP()
{
	CloseHandle(m_IOCPHandle);
}

void IOCP::RegisterEvent(shared_ptr<Session> _pSession)
{
	HANDLE handle = _pSession->GetHandle();
	CreateIoCompletionPort(handle, m_IOCPHandle, 0, 0 );

}

void IOCP::RegisterDummyPacket()
{
	PostQueuedCompletionStatus(m_IOCPHandle, 0, 0, nullptr);
}

void IOCP::Excute()
{
	DWORD numOfBytes = 0;
	ULONG_PTR key = 0;
	IOCPEvent* iocpEvnet = nullptr;

	if (GetQueuedCompletionStatus(m_IOCPHandle, &numOfBytes, &key, reinterpret_cast<LPOVERLAPPED*>(&iocpEvnet), INFINITE) != false)
	{
		if (iocpEvnet == nullptr)
			return;
			
		shared_ptr<Session> pSession = iocpEvnet->GetOwner();
		pSession->DisPatch(iocpEvnet, numOfBytes);
	}
	else
	{
		int error = GetLastError();
		if(error == WAIT_TIMEOUT)
			return;
		else
		{
			shared_ptr<Session> pSession = iocpEvnet->GetOwner();
			pSession->DisPatch(iocpEvnet, numOfBytes);
		}
	}
}

#include "pch.h"
#include "Listener.h"
#include "IOCP.h"
#include "IOCPEvent.h"
#include "SockHelper.h"
#include "Service.h"
#include "NetAddress.h"

Listener::Listener()
{

}

Listener::~Listener()
{
	SockHelper::Close(m_socket);

	for (IOCPAcceptEvent* pEvent : m_vecEvent)
	{
		delete pEvent;
	}
}

void Listener::Clear()
{
	for (IOCPAcceptEvent* pEvent : m_vecEvent)
	{
		pEvent->SetOwner(nullptr);
	}
}

void Listener::Start()
{
	m_socket = SockHelper::Create_Socket();
	
	
	GetService()->GetIOCP()->RegisterEvent(shared_from_this());
	
	if (SockHelper::SetReuseAddress(m_socket, true) == false)
		assert(nullptr);

	if (SockHelper::SetLinger(m_socket, 0, 0) == false)
		assert(nullptr);
	
	if (SockHelper::Bind(m_socket, GetService()->GetAddress()) == false)
		assert(nullptr);

	if (SockHelper::Listen(m_socket, SOMAXCONN) == false)
		assert(nullptr);
	

	UINT AcceptCount = GetService()->GetMaxSessionCount();

	for (UINT i = 0; i < AcceptCount; ++i)
	{
		IOCPAcceptEvent* pAcceptEvent = new IOCPAcceptEvent();
		pAcceptEvent->SetOwner(shared_from_this()); //내 listensocket 등록

		m_vecEvent.push_back(pAcceptEvent);
		RegisterAccept(pAcceptEvent);
	}
}

void Listener::DisPatch(IOCPEvent* _pEvent, int _iNumOfBytes)
{
	//행당 event를 등록하고 사라지면 문제가 발생 -> shared로 바꾸기
	IOCPAcceptEvent* pAccept = static_cast<IOCPAcceptEvent*>(_pEvent);
	pAccept->GetOwner()->ProcessAccept(pAccept);
	
}

void Listener::RegisterAccept(IOCPAcceptEvent* _pAcceptEvent)
{
	//클라 소켓
	shared_ptr<Session> pSession = GetService()->CreateSession(); //여기서 클라전용 세션으로
	
	_pAcceptEvent->init();
	_pAcceptEvent->m_pSession = pSession; //내 클라소켓 등록 (서버에서 클라랑 데이터를 주고받기 위해)


	DWORD bytesRecved = 0;
	
	if (false == SockHelper::AcceptEx(m_socket, pSession->GetSocket(), pSession->m_recvBuffer.GetWritePos(), 0,
		sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &bytesRecved, reinterpret_cast<LPOVERLAPPED>(_pAcceptEvent)))
	{
		const int errorCode = WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			//만약 실패하면 다시 accept
			RegisterAccept(_pAcceptEvent);
		}
	}
}

void Listener::ProcessAccept(IOCPAcceptEvent* _pAcceptEvent)
{
	shared_ptr<Session> session = _pAcceptEvent->m_pSession; //아까 만들어둔 클라소켓

	//서버로 (서버에서 클라와 소통하기위한 소캣)
	if (SockHelper::SetUpdateAcceptSocket(session->GetSocket(), m_socket) == false)
		assert(nullptr);

	SOCKADDR_IN clientAddr;
	int iAddrSize = sizeof(clientAddr);
	if (getpeername(session->GetSocket(), reinterpret_cast<SOCKADDR*>(&clientAddr), &iAddrSize) == SOCKET_ERROR)
	{
		RegisterAccept(_pAcceptEvent);
	}

	session->SetAddress(NetAddress(clientAddr));

	//connected
	session->ProcessConnect();
	
	RegisterAccept(_pAcceptEvent);

}

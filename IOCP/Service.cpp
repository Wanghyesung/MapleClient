#include "pch.h"
#include "Service.h"
#include "NetAddress.h"
#include "SockHelper.h"
#include "IOCP.h"
#include "Session.h"
#include "Listener.h"


Service::Service(eServiceType _eType, NetAddress _addr, shared_ptr<IOCP> _pIOCP, function<shared_ptr<Session>(void)> _pCreateSessionFunc, UINT _iMaxSessionCount) :
	m_etype(_eType),
	m_Address(_addr),
	m_pIOCP(_pIOCP),
	m_FuncCreateSession(_pCreateSessionFunc),
	m_iMaxSessionCount(_iMaxSessionCount)
{
	
}

Service::~Service()
{

}

shared_ptr<Session> Service::CreateSession()
{
	if (m_FuncCreateSession == nullptr)
		assert(nullptr);

	shared_ptr<Session> pSession = m_FuncCreateSession();
	pSession->SetService(shared_from_this());

	//iocp등록
	m_pIOCP->RegisterEvent(pSession);

	return pSession;
}

void Service::AddSession(shared_ptr<Session> _pSession)
{
	WLock lock(m_Lock);
	m_setSession.insert(_pSession);
}

void Service::EraseSession(shared_ptr<Session> _pSession)
{
	WLock lock(m_Lock);
	m_setSession.erase(_pSession);
}

void Service::BroadCast(shared_ptr<SendBuffer> _pSendBuffer)
{
	for (auto& session : m_setSession)
	{
		session->Send(_pSendBuffer);
	}
}


ServerService::ServerService(NetAddress _addr, shared_ptr<IOCP> _pIOCP, function<shared_ptr<Session>(void)> _pCreateSessionFunc, UINT _iMaxSessionCount):
	Service(eServiceType::Server,_addr, _pIOCP, _pCreateSessionFunc, _iMaxSessionCount)
{

}

ServerService::~ServerService()
{

}



void ServerService::Start()
{
	if (SockHelper::Start())
		assert(nullptr);

	
	m_pLisener = make_shared<Listener>();
	m_pLisener->SetService(static_pointer_cast<ServerService>(shared_from_this()));
	m_pLisener->Start();

}




ClientService::ClientService(NetAddress _targetAddr, shared_ptr<IOCP> _pIOCP, function<shared_ptr<Session>(void)> _pCreateSessionFunc, UINT _iMaxSessionCount):
	Service(eServiceType::Client, _targetAddr, _pIOCP, _pCreateSessionFunc, _iMaxSessionCount)
{

}

ClientService::~ClientService()
{
	m_pClientSession->Clear();
}

void ClientService::Start()
{
	if (GetServiceType() != eServiceType::Client)
	{
		return;
	}

	SockHelper::Start();

	m_pClientSession = CreateSession();
	//int iCount = GetMaxSessionCount();
	//
	//for (int i = 0; i < iCount; ++i)
	//{
	//	shared_ptr<Session> pSession = CreateSession();
	//	pSession->Connect();
	//}

}

void ClientService::Stop()
{
	// IOCP 스레드를 강제 종료할 수 있도록 종료 패킷 전송
	for (int i = 0; i < 5; ++i)  // 실행 중인 스레드 개수만큼
	{
		GetIOCP()->RegisterDummyPacket();
	}
}

void ClientService::Connect()
{
	if (m_pClientSession == nullptr)
		assert(nullptr);

	m_pClientSession->Connect();
}

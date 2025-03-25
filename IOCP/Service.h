#pragma once

#include "NetAddress.h"
#include "RWLock.h"
#include <functional>

class IOCP;
class Session;
class Listener;
class SendBuffer;
enum eServiceType
{
	Client,
	Server,

};
class Service : public enable_shared_from_this<Service>
{
public:
	//Service(const wstring& _strAddr , UINT _iProt);
	Service(eServiceType _eType, NetAddress _addr, shared_ptr<IOCP> _pIOCP, function<shared_ptr<Session>(void)> _pCreateSessionFunc, UINT _iMaxSessionCount);
	virtual ~Service();

	virtual void Start() =0;

	shared_ptr<Session> CreateSession();

	NetAddress GetAddress() { return m_Address; }
	shared_ptr<IOCP> GetIOCP() { return m_pIOCP; }
	UINT GetMaxSessionCount() { return m_iMaxSessionCount; }
	eServiceType GetServiceType() { return m_etype; }
	shared_ptr<Service> GetServiceShared() { return shared_from_this(); }

	void AddSession(shared_ptr<Session> _pSession);
	void EraseSession(shared_ptr<Session> _pSession);


	void BroadCast(shared_ptr<SendBuffer> _pSendBuffer);
private:
	NetAddress m_Address;
	shared_ptr<IOCP> m_pIOCP;
	set<shared_ptr<Session>> m_setSession;
	eServiceType m_etype;
	
	function<shared_ptr<Session>(void)> m_FuncCreateSession;

	UINT m_iMaxSessionCount;

	RWLock m_Lock;
};




class ServerService : public Service
{
public:
	ServerService(NetAddress _addr, shared_ptr<IOCP> _pIOCP, function<shared_ptr<Session>(void)> _pCreateSessionFunc, UINT _iMaxSessionCount);
	virtual ~ServerService();


public:
	virtual void Start() override;


private:
	shared_ptr<Listener> m_pLisener;
};


class ClientService : public Service
{
public:
	ClientService(NetAddress _targetAddr, shared_ptr<IOCP> _pIOCP, function<shared_ptr<Session>(void)> _pCreateSessionFunc, UINT _iMaxSessionCount);
	virtual ~ClientService();


public:
	virtual void Start() override;
	void Stop();
	void Connect();
	shared_ptr<Session> GetClientSession() { return m_pClientSession; }

private:
	shared_ptr<Session> m_pClientSession; 
};
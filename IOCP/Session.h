#pragma once

#include "NetAddress.h"
#include "IOCPEvent.h"
#include "RecvBuffer.h"
#include "SendBuffer.h"

class IOCPEvent;
class Service;
class RecvBuffer;

enum
{
	BUFFER_SIZE = 0x10000
};

class Session : public enable_shared_from_this<Session>
{
	friend class Listener;

public:
	Session();
	virtual ~Session();

	virtual void DisPatch(IOCPEvent* _pEvent, int _iNumOfBytes);

	void SetService(shared_ptr<Service> _pService) { m_weakService = _pService; }
	void SetAddress(NetAddress _Address) { m_Address = _Address; }

	HANDLE GetHandle() { return reinterpret_cast<HANDLE>(m_socket);}
	SOCKET GetSocket() { return m_socket; }
	shared_ptr<Service> GetService() { return m_weakService.lock(); }

	virtual void Clear();
public:
	virtual void RegisterAccept(IOCPAcceptEvent* _pIocpEvent) {};
	virtual void ProcessAccept(IOCPAcceptEvent* _pIocpEvent) {};

	virtual void RegisterConnect();
	virtual void ProcessConnect();

	virtual void RegisterDisConnect();
	virtual void ProcessDisConnect();

	virtual void RegisterSend();
	virtual void ProcessSend(int _iNumOfBytes);

	virtual void RegisterRecv();
	virtual void ProcessRecv(int _iNumOfBytes);

	void HandleError(int iErrorCode);
public:
	void DisConnect(const WCHAR* _strCause);
	void Connect();
	void Send(shared_ptr<SendBuffer> _pBuffer);
	//void Recv();
protected:
	//만약 연결이 되었을 때 실행할 함수 
	//(특정 동작이 되었을 때 실행할 함수들)
	virtual void OnConnected() {};
	virtual int OnRecv(BYTE* buffer, int len) { return len; }
	virtual void OnSend(int len) {}
	virtual void OnDisConnected() {}


private:
	SOCKET m_socket;
	weak_ptr<Service> m_weakService;//순환 참조
	NetAddress m_Address;
	atomic<bool> m_bConnected;

	IOCPConnectEvent m_ConnectEvent;
	ICOPDisConnectEvent m_DisConnectEvent;
	IOCPSendEvent m_sendEvent;
	IOCPRecvEvent m_recvEvent;


private:
	RWLock m_lock;


	//IOCP는 동시에 두 개 이상의 Recv 작업을 같은 소켓에서 처리하지 않습니다.
	RecvBuffer m_recvBuffer;

	//같은 세션 객체(Session)에 대해 여러 스레드가 동시에 접근할 가능성이 있습니다
	queue<shared_ptr<SendBuffer>> m_qSendBuffer;
	atomic<bool> m_atRegisterSend;

	/*
	16-3-2 순서로 전송했는데 3이 16바이트 중간에 끼어들어서 전송될 수는 없습니다. 다만 16+3 이렇게 19바이트가 한 번에 올 수는 있겠죠.
	*/

};


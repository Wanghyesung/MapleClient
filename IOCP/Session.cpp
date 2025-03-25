#include "pch.h"
#include "Session.h"
#include "IOCPEvent.h"
#include "SockHelper.h"
#include "Service.h"
#include "IOCP.h"
#include "NetAddress.h"

Session::Session() :
	m_bConnected(false),
	m_atRegisterSend(false),
	m_recvBuffer(BUFFER_SIZE),
	m_lock{}
{
	m_socket = SockHelper::Create_Socket();
}

Session::~Session()
{
	SockHelper::Close(m_socket);
}

void Session::DisPatch(IOCPEvent* _pEvent, int _iNumOfBytes)
{
	eIocpEvent eEvent = _pEvent->GetEvent();
	switch (eEvent)
	{
	case eIocpEvent::Connect:
		ProcessConnect();
		break;

	case eIocpEvent::DisConnect:
		ProcessDisConnect();
		break;

	case eIocpEvent::Send:
		ProcessSend(_iNumOfBytes);
		break;

	case eIocpEvent::Recv:
		ProcessRecv(_iNumOfBytes);
		break;
	default:
		break;
	}
}


void Session::DisConnect(const WCHAR* _strCause)
{
	if (m_bConnected.exchange(false) == false)
		return;

	wcout << _strCause;

	RegisterDisConnect();
	//GetService()->EraseSession(shared_from_this());

}

void Session::Connect()
{
	RegisterConnect();
}

void Session::Send(shared_ptr<SendBuffer> _pBuffer)
{
	WLock lockguard(m_lock);
	m_qSendBuffer.push(_pBuffer); 

	if (m_atRegisterSend.exchange(true) == false)
		RegisterSend();
}

void Session::Clear()
{
	m_ConnectEvent.SetOwner(nullptr);
	m_DisConnectEvent.SetOwner(nullptr);
	m_sendEvent.SetOwner(nullptr);
	m_recvEvent.SetOwner(nullptr);
}

void Session::RegisterConnect()
{	
	if (GetService()->GetServiceType() != eServiceType::Client)
		return;


	if (SockHelper::SetReuseAddress(m_socket, true) == false)
		assert(nullptr);

	//누락하면 에러
	if (SockHelper::BindAny(m_socket, 0/*남는 포트, 주소번호로*/) == false)
		assert(nullptr);

	m_ConnectEvent.init();
	m_ConnectEvent.SetOwner(shared_from_this());

	DWORD iNumOfBytes = 0;
	SOCKADDR_IN sockAddr = GetService()->GetAddress().GetAddr();
	if (false == SockHelper::ConnectEx(m_socket, reinterpret_cast<SOCKADDR*>(&sockAddr), sizeof(sockAddr), nullptr, 0, &iNumOfBytes, &m_ConnectEvent))
	{
		int errorCode = WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			m_ConnectEvent.SetOwner(nullptr);
			assert(nullptr);
		}
	}
}

void Session::ProcessConnect()
{
	m_ConnectEvent.SetOwner(nullptr);
	//내 서버에 넣기
	m_bConnected.store(true);

	GetService()->AddSession(shared_from_this());

	//오버라이딩
	OnConnected();

	//수신 등록 
	RegisterRecv();
}

void Session::RegisterDisConnect()
{
	m_DisConnectEvent.SetOwner(shared_from_this());
	m_DisConnectEvent.init();


	if (SockHelper::DisConnectEx(m_socket, &m_DisConnectEvent, TF_REUSE_SOCKET, 0) != false)
	{
		int errorCode = WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			assert(nullptr);
		}
	}
}

void Session::ProcessDisConnect()
{
	m_DisConnectEvent.SetOwner(nullptr); //참조 해제

	GetService()->EraseSession(shared_from_this()); //lock

	OnDisConnected();

}

void Session::RegisterSend()
{
	m_sendEvent.SetOwner(shared_from_this()); //나를 들고있게 해서 바로 해제하지 못하게 (원본 Event유지)
	m_sendEvent.init();

	{
		WLock lockguard(m_lock);

		int iWriteSize = 0;
		while (!m_qSendBuffer.empty())//WSAbuffer에 버퍼가 사라지지 않기를 보장하기 위해서
		{
			shared_ptr<SendBuffer> pSendBuffer = m_qSendBuffer.front();
			m_qSendBuffer.pop();

			iWriteSize += pSendBuffer->GetWritePos();
			m_sendEvent.m_vecSendBuffer.push_back(pSendBuffer);
		}
	}

	vector<WSABUF> vecWsaBuf = {};
	vecWsaBuf.reserve(m_sendEvent.m_vecSendBuffer.size());

	for (int i = 0; i < m_sendEvent.m_vecSendBuffer.size(); ++i)
	{
		WSABUF wsaBuf = {};
		wsaBuf.buf = reinterpret_cast<char*>(m_sendEvent.m_vecSendBuffer[i]->GetData());
		wsaBuf.len = static_cast<DWORD>(m_sendEvent.m_vecSendBuffer[i]->GetWritePos());
		vecWsaBuf.push_back(wsaBuf);
	}


	DWORD sendBytes = 0;
	if (WSASend(m_socket, vecWsaBuf.data(), static_cast<DWORD>(vecWsaBuf.size()), &sendBytes, 0, &m_sendEvent, nullptr) != false)
	{
		int errorCode = WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			HandleError(errorCode);
			m_sendEvent.SetOwner(nullptr);
			m_sendEvent.m_vecSendBuffer.clear();
			m_atRegisterSend.store(false);
		}
	}
}

void Session::ProcessSend(int _iNumOfBytes)
{
	m_sendEvent.m_vecSendBuffer.clear();
	m_sendEvent.SetOwner(nullptr);

	if (_iNumOfBytes == 0)
	{
		DisConnect(L"Recv 0");
		return;
	}

	OnSend(_iNumOfBytes);

	if (m_qSendBuffer.empty())
		m_atRegisterSend.store(false);
	else
		RegisterSend();
}

void Session::RegisterRecv()
{
	m_recvEvent.init();
	m_recvEvent.SetOwner(shared_from_this());

	WSABUF wsaBuf = {};
	wsaBuf.buf = reinterpret_cast<char*>(m_recvBuffer.GetWritePos());//writePos 위치의 버퍼부터
	wsaBuf.len = 1024;

	DWORD numOfBytes = 0;
	DWORD flag = 0;

	if(WSARecv(m_socket, &wsaBuf, 1, &numOfBytes, &flag, &m_recvEvent, nullptr) != false)
	{
		int errorCode = WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			HandleError(errorCode);
			m_recvEvent.SetOwner(nullptr);
			//assert(nullptr);
		}
	}
}

void Session::ProcessRecv(int _iNumOfBytes)
{
	m_recvEvent.SetOwner(nullptr);

	if (_iNumOfBytes == 0)
	{
		//연결이 끊김
		DisConnect(L"Recv 0");
		return;
	}

	if (m_recvBuffer.Write(_iNumOfBytes) == false)
	{
		DisConnect(L"RecvWrite Overflow");
		return;
	}

	int proccessLen = OnRecv(m_recvBuffer.GetReadPos(), _iNumOfBytes);

	if (proccessLen < 0 || proccessLen < m_recvBuffer.DataSize() ||
		m_recvBuffer.Read(_iNumOfBytes) == false)
	{
		DisConnect(L"RecvRead Overflow");
		return;
	}

	m_recvBuffer.Clear();

	RegisterRecv();
}

void Session::HandleError(int iErrorCode)
{
	switch (iErrorCode)
	{
	case WSAECONNRESET:
	case WSAECONNABORTED:
		DisConnect(L"HandleError");
		break;

	default:
		cout << "Handle Eerror : " << iErrorCode << endl;
		break;
	}
}

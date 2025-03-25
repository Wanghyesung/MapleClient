#pragma once


class NetAddress;

class SockHelper
{
	//비동기 연결 소켓 함수
public:
	static void init();

	static bool BindWindowFunc(SOCKET _socket,  GUID WSAID, LPVOID* _pFunc);
	
public:
	static LPFN_CONNECTEX ConnectEx;
	static LPFN_DISCONNECTEX DisConnectEx;
	static LPFN_ACCEPTEX AcceptEx;

public:
	static SOCKET Create_Socket();
	
	//option
	static bool SetLinger(SOCKET _socket, int _iOnoff, int _iLinger);
	static bool SetReuseAddress(SOCKET _socket, bool _bFlag);
	static bool SetRecvBufferSize(SOCKET _socket, int _iSize);
	static bool SetSendBufferSize(SOCKET _socket, int _iSize);
	static bool SetTcpNoDelay(SOCKET _socket, bool _bFlag);
	static bool SetUpdateAcceptSocket(SOCKET _socket, SOCKET _listenSocket);


public:
	static bool Start();
	static bool Close(SOCKET& _socket);
	static bool Clear();
	static bool Bind(SOCKET _socket, NetAddress addr);
	static bool BindAny(SOCKET _socket, UINT _iPort);
	static bool Listen(SOCKET _socket, int backlog);

private:
	
};


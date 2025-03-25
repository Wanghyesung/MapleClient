#pragma once
class NetAddress
{
public:
	NetAddress() = default;
	NetAddress(const wstring& _sAddr, UINT _iPort);
	NetAddress(SOCKADDR_IN _addr);
	~NetAddress();

	SOCKADDR_IN& GetAddr() { return m_sockAddr; }
	wstring			GetIpAddress();
private:
	SOCKADDR_IN m_sockAddr;
};


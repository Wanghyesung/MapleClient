#include "pch.h"
#include "NetAddress.h"

NetAddress::NetAddress(const wstring& _sAddr, UINT _iPort)
{
	memset(&m_sockAddr, 0, sizeof(m_sockAddr));
	m_sockAddr.sin_family = AF_INET;

	IN_ADDR addr;
	InetPtonW(AF_INET, _sAddr.c_str(), &addr);
	m_sockAddr.sin_addr = addr;
	m_sockAddr.sin_port = htons(_iPort);
}

NetAddress::NetAddress(SOCKADDR_IN _addr):
	m_sockAddr(_addr)
{
}

NetAddress::~NetAddress()
{

}

wstring NetAddress::GetIpAddress()
{
	WCHAR Buff[100];
	InetNtopW(AF_INET, &m_sockAddr.sin_addr, Buff, sizeof(Buff));

	return wstring(Buff);
}

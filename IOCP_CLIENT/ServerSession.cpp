#include "pch.h"
#include "ServerSession.h"
#include "Enter.pb.h"
#include "ServerPacketHandler.h"
#include "NetFunc.h"

extern string PLAYER_NAME;

ServerSession::ServerSession()
{

}

ServerSession::~ServerSession()
{

}

void ServerSession::OnConnected()
{
	Protocol::C_ENTER pkt;
	
	//const wstring& strClientName = to_wstring();
	pkt.set_name(PLAYER_NAME);

	shared_ptr<SendBuffer> pSendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
	
	Send(pSendBuffer);
}

int ServerSession::OnRecvPacket(BYTE* buffer, int len)
{
	shared_ptr<PacketSession> pSession = GetPacketSessionRef();
	ServerPacketHandler::HandlePacket(pSession, buffer, len);

	return len;
}

void ServerSession::OnSend(int len)
{

}

void ServerSession::OnDisConnected()
{
}

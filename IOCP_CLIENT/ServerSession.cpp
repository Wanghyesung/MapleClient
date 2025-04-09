#include "pch.h"
#include "ServerSession.h"
#include "Enter.pb.h"
#include "ServerPacketHandler.h"
ServerSession::ServerSession()
{

}

ServerSession::~ServerSession()
{

}

void ServerSession::OnConnected()
{
	//Protocol::C_ENTER pkt;
	//
	//const wstring& strClientName = CRoomMgr::GetInst()->GetClientName();
	//
	//pkt.set_name(WstringToString(strClientName));
	//shared_ptr<SendBuffer> pSendBuffer = CServerPacketHandler::MakeSendBuffer(pkt);
	//
	//GClientService->GetClientSession()->Send(pSendBuffer);
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

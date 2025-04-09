#include "pch.h"
#include "ServerPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_S_ENTER(shared_ptr<Session> _pSession, Protocol::S_ENTER& _pkt)
{
	return false;
}

bool Handle_S_NEW_ENTER(shared_ptr<Session> _pSession, Protocol::S_NEW_ENTER& _pkt)
{
	return false;
}

bool Handle_S_EQUIP(shared_ptr<Session> _pSession, Protocol::S_EQUIP& _pkt)
{
	return false;
}

bool Handle_S_MAP(shared_ptr<Session> _pSession, Protocol::S_MAP& _pkt)
{
	return false;
}

bool Handle_S_CREATE(shared_ptr<Session> _pSession, Protocol::S_CREATE& _pkt)
{
	return false;
}

bool Handle_S_DELETE(shared_ptr<Session> _pSession, Protocol::S_DELETE& _pkt)
{
	return false;
}

bool Handle_S_STATE(shared_ptr<Session> _pSession, Protocol::S_STATE& _pkt)
{
	return false;
}

bool Handle_S_TRANSFORM(shared_ptr<Session> _pSession, Protocol::S_TRANSFORM& _pkt)
{
	return false;
}

bool Handle_S_EXIT(shared_ptr<Session> _pSession, Protocol::S_EXIT& _pkt)
{
	return false;
}

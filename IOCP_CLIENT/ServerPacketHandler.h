#pragma once

#include "PacketSession.h"
#include "Enter.pb.h"
#include "Exit.pb.h"
#include "Collision.pb.h"
#include "Equip.pb.h"
#include "Input.pb.h"
#include "Map.pb.h"
#include "Transform.pb.h"
#include "GameObject.pb.h"
#include "ObjectState.pb.h"
#include "Service.h"

extern shared_ptr< ClientService> GClientService;
using PacketHandlerFunc = std::function<bool(shared_ptr<PacketSession>&, BYTE*, INT)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];
//기본 : ID, LAYER, SCENE

enum PACKET_TYPE
{
	S_ENTER = 1000,
	C_ENTER = 1001, //클라가 서버에게
	S_NEW_ENTER = 1002,

	S_COLLISION = 1003,

	S_EQUIP = 1004,
	C_EQUIP = 1005, //클라가 서버에게

	C_INPUT = 1006,

	S_MAP = 1007,

	S_CREATE = 1008,
	C_CREATE = 1009,
	S_DELETE = 1010,


	//물체 위치
	S_STATE = 1011,

	S_TRANSFORM = 1012,

	S_EXIT = 1013,
	C_EXIT = 1014,
	S_NEW_EXIT = 1015,
};


template <typename T>
shared_ptr<SendBuffer> _MakeSendBuffer(T& _pkt, UINT _ID);

//서버에서 온 패킷 처리
bool Handle_S_ENTER(shared_ptr<Session> _pSession, Protocol::S_ENTER& _pkt);
bool Handle_S_NEW_ENTER(shared_ptr<Session> _pSession, Protocol::S_NEW_ENTER& _pkt);
bool Handle_S_EQUIP(shared_ptr<Session> _pSession, Protocol::S_EQUIP& _pkt);
bool Handle_S_MAP(shared_ptr<Session> _pSession, Protocol::S_MAP& _pkt);
bool Handle_S_CREATE(shared_ptr<Session> _pSession, Protocol::S_CREATE& _pkt);
bool Handle_S_DELETE(shared_ptr<Session> _pSession, Protocol::S_DELETE& _pkt);
bool Handle_S_STATE(shared_ptr<Session> _pSession, Protocol::S_STATE& _pkt);
bool Handle_S_TRANSFORM(shared_ptr<Session> _pSession, Protocol::S_TRANSFORM& _pkt);
bool Handle_S_EXIT(shared_ptr<Session> _pSession, Protocol::S_EXIT& _pkt);


class ServerPacketHandler
{
public:
	static bool HandlePacket(shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
	{
		PacketHeader* pHeader = reinterpret_cast<PacketHeader*>(_pBuffer);
		return GPacketHandler[pHeader->id](_pSession, _pBuffer, _iLen);
	}

	static void Initialize()
	{
		GPacketHandler[S_ENTER] = [](shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
			{return  HandlePacket<Protocol::S_ENTER>(Handle_S_ENTER, _pSession, _pBuffer, _iLen); };
		GPacketHandler[S_NEW_ENTER] = [](shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
			{return  HandlePacket<Protocol::S_NEW_ENTER>(Handle_S_NEW_ENTER, _pSession, _pBuffer, _iLen); };
		GPacketHandler[S_EQUIP] = [](shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
			{return  HandlePacket<Protocol::S_EQUIP>(Handle_S_EQUIP, _pSession, _pBuffer, _iLen); };
		GPacketHandler[S_MAP] = [](shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
			{return  HandlePacket<Protocol::S_MAP>(Handle_S_MAP, _pSession, _pBuffer, _iLen); };
		GPacketHandler[S_CREATE] = [](shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
			{return  HandlePacket<Protocol::S_CREATE>(Handle_S_CREATE, _pSession, _pBuffer, _iLen); };
		GPacketHandler[S_DELETE] = [](shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
			{return  HandlePacket<Protocol::S_DELETE>(Handle_S_DELETE, _pSession, _pBuffer, _iLen); };
		GPacketHandler[S_STATE] = [](shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
			{return  HandlePacket<Protocol::S_STATE>(Handle_S_STATE, _pSession, _pBuffer, _iLen); };
		GPacketHandler[S_TRANSFORM] = [](shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
			{return  HandlePacket<Protocol::S_TRANSFORM>(Handle_S_TRANSFORM, _pSession, _pBuffer, _iLen); };
	}

	template <typename T, typename Func>
	static bool HandlePacket(Func _pFunc, shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
	{
		T pkt;
		if (pkt.ParseFromArray(_pBuffer + sizeof(PacketHeader), _iLen - sizeof(PacketHeader)) == false)
			return false;

		return _pFunc(_pSession, pkt);
	}

	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_ENTER _pkt) { return _MakeSendBuffer(_pkt, C_ENTER); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_CREATE _pkt) { return _MakeSendBuffer(_pkt, C_CREATE); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_INPUT _pkt) { return _MakeSendBuffer(_pkt, C_INPUT); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_EQUIP _pkt) { return _MakeSendBuffer(_pkt, C_EQUIP); }
	
};



template<typename T>
inline shared_ptr<SendBuffer> _MakeSendBuffer(T& _pkt, UINT _ID)
{
	const UINT16 iDataSize = static_cast<UINT16>(_pkt.ByteSizeLong());
	const UINT16 iPacketSize = iDataSize + sizeof(PacketHeader);
	shared_ptr<SendBuffer> pSendBuffer = SendBufferMgr->Open(iPacketSize);

	PacketHeader* pHeader = reinterpret_cast<PacketHeader*>(pSendBuffer->GetData());
	pHeader->id = _ID;
	pHeader->size = iPacketSize;
	_pkt.SerializeToArray(&pHeader[1], iDataSize);

	pSendBuffer->Close(iPacketSize);
	return pSendBuffer;
}



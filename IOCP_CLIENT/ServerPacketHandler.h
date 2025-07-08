#pragma once

#include "PacketSession.h"
#include "Enter.pb.h"
#include "Exit.pb.h"
#include "Equip.pb.h"
#include "Input.pb.h"
#include "Map.pb.h"
#include "Transform.pb.h"
#include "GameObject.pb.h"
#include "ObjectState.pb.h"
#include "Skill.pb.h"
#include "Service.h"

extern shared_ptr< ClientService> GClientService;
using PacketHandlerFunc = std::function<bool(shared_ptr<PacketSession>&, BYTE*, INT)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

extern unordered_map<string, wstring> GHashStringToWstring;
extern unordered_map<wstring, string> GHashWstringToString;

#define LOG_PACKET_SEND(name) \
    do { \
        char buf[256]; \
        std::snprintf(buf, sizeof(buf), \
            "[Client] Packet sent: %s (%s:%d)\n", \
            #name, __FILE__, __LINE__); \
        OutputDebugStringA(buf); \
    } while(0)


enum PACKET_TYPE
{
	S_ENTER = 1000,
	C_ENTER = 1001,
	S_NEW_ENTER = 1002,

	S_COLLISION = 1003,

	S_EQUIP = 1004,
	C_EQUIP = 1005,

	C_INPUT = 1006,

	S_MAP = 1007,
	C_MAP = 1008,
	C_MAP_LOADING = 1009,

	S_START_MAP = 1010,
	C_START_MAP = 1011,

	S_CREATE = 1012,
	C_CREATE = 1013,
	S_DELETE = 1014,


	//물체 위치
	S_STATE = 1015,

	S_TRANSFORM = 1016,

	S_SKILL = 1017,
	C_SKILL = 1018,

	S_EXIT = 1019,
	C_EXIT = 1020,
	S_NEW_EXIT = 1021,
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
bool Handle_S_SKILL(shared_ptr<Session> _pSession, Protocol::S_Skill& _pkt);
bool Handle_S_START_MAP(shared_ptr<Session> _pSession, Protocol::S_START_MAP& _pkt);
bool Handle_S_EXIT(shared_ptr<Session> _pSession, Protocol::S_EXIT& _pkt);
bool Handle_S_NEW_EXIT(shared_ptr<Session> _pSession, Protocol::S_NEW_EXIT& _pkt);


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
		GPacketHandler[S_SKILL] = [](shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
			{return  HandlePacket<Protocol::S_Skill>(Handle_S_SKILL, _pSession, _pBuffer, _iLen); };
		GPacketHandler[S_START_MAP] = [](shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
			{return  HandlePacket<Protocol::S_START_MAP>(Handle_S_START_MAP, _pSession, _pBuffer, _iLen); };
		GPacketHandler[S_TRANSFORM] = [](shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
			{return  HandlePacket<Protocol::S_TRANSFORM>(Handle_S_TRANSFORM, _pSession, _pBuffer, _iLen); };
		GPacketHandler[S_NEW_EXIT] = [](shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
			{return  HandlePacket<Protocol::S_NEW_EXIT>(Handle_S_NEW_EXIT, _pSession, _pBuffer, _iLen); };
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
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_MAP _pkt) { return _MakeSendBuffer(_pkt, C_MAP); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_MAP_LOADING _pkt) { return _MakeSendBuffer(_pkt, C_MAP_LOADING); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_Skill _pkt) { return _MakeSendBuffer(_pkt, C_SKILL); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_START_MAP _pkt) { return _MakeSendBuffer(_pkt, C_START_MAP); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_EXIT _pkt) { return _MakeSendBuffer(_pkt, C_EXIT); }
	
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



#pragma once

#include "PacketSession.h"

using PacketHandlerFunc = std::function<bool(shared_ptr<PacketSession>&, BYTE*, INT)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];
//기본 : ID, LAYER, SCENE

enum PACKET_TYPE
{
	S_ENTER = 1000,
	C_ENTER = 1001, //클라가 서버에게
	S_NEW_ENTER = 1002,

	//물체 위치
	S_TRANSFORM = 1003,

	//새 물체
	/*
	{
  "1001": {
    "name": "Goblin",
    "model": "Models/Goblin.fbx",
    "anim_idle": "Anims/goblin_idle.anim",
    "anim_attack": "Anims/goblin_attack.anim"
  }
	생성될때만 보내고 클라에서는 리소스 로딩
	그 후에는 애니메이션 인덱스만 보내기 STATE : STATE : string, ANIM_IDX : int
	*/
	S_NEW_OBJECT = 1006,

	//맵 이동
	S_CHANAGE_MAP = 1007,

	//물체 생성
	S_PLAYER_STATE = 1008,

	//클라가 서버에게 누른 키값 전달
	C_PLAYER_INPUT = 1009,

	//충돌
	S_COLLISION = 1010,

	//클라 인벤에서 옷 변경
	S_EQUIP = 1011,
	C_EQUIP = 1012,
	S_NEW_EQUIP = 1012,


	S_EXIT = 1013,
	C_EXIT = 1014,
	S_NEW_EXIT = 1015,
};


template <typename T>
shared_ptr<SendBuffer> _MakeSendBuffer(T& _pkt, UINT _ID);

class ServerPacketHandler
{
	static bool HandlePacket(shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
	{
		PacketHeader* pHeader = reinterpret_cast<PacketHeader*>(_pBuffer);
		return GPacketHandler[pHeader->id](_pSession, _pBuffer, _iLen);
	}

	static void Initialize()
	{
		GPacketHandler[S_ENTER] = [](shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
			{return 1; };
	}

	template <typename T, typename Func>
	static bool HandlePacket(Func _pFunc, shared_ptr<PacketSession>& _pSession, BYTE* _pBuffer, INT _iLen)
	{
		T pkt;
		if (pkt.ParseFromArray(_pBuffer + sizeof(PacketHeader), _iLen - sizeof(PacketHeader)) == false)
			return false;

		return _pFunc(_pSession, pkt);
	}
};


template<typename T>
inline shared_ptr<SendBuffer> _MakeSendBuffer(T& _pkt, UINT _ID)
{
	return shared_ptr<SendBuffer>();
}

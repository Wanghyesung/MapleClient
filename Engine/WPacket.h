#pragma once
#include "WPacketManager.h"


namespace W
{
	enum ePacketType
	{
		S_ENTER = 1000,
		C_ENTER = 1001, 
		S_NEW_ENTER = 1002,

		S_COLLISION = 1003,

		S_EQUIP = 1004,
		C_EQUIP = 1005, 

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

		END = 1099,
	};

	class Packet
	{
	public:
		Packet(ePacketType _eType):
			m_eType(_eType) {};
		virtual	~Packet() {};

	public:
		void SendPacket() { PacketManager::AddPacket(this); };
		virtual void Send() = 0;

		ePacketType GetPacketType() { return m_eType; }
	private:
		ePacketType m_eType;

		friend class PacketManager;
	};

}

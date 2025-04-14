#pragma once
#include "Engine.h"


namespace W
{
	class Packet;

	class PacketManager
	{
	public:
		//Engine에서 순차적으로 접근 Lock X
		static void AddPacket(Packet* _pPacket);
		static void Update();
	private:
		static std::queue<Packet*> m_queuePacket;

		
	};
}

#pragma once
#include "WPacketManager.h"
#include "Engine.h"

namespace W
{
	class Packet
	{
	public:
		Packet() {};
		virtual	~Packet() {};

	public:
		void SendPacket() { PacketManager::AddPacket(this); };
		virtual void Send() = 0;
	};

}

#include "WPacketManager.h"
#include "WPacket.h"

namespace W
{
	std::queue<Packet*> PacketManager::m_queuePacket = {};

	void PacketManager::AddPacket(Packet* _pPacket)
	{
		m_queuePacket.push(_pPacket);
	}

	void PacketManager::Update()
	{
		while (!m_queuePacket.empty())
		{
			Packet* pPacket = m_queuePacket.front();
			m_queuePacket.pop();
			pPacket->Send();
		}
	}
}


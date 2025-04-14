#include "WInputPacket.h"
#include "Engine.h"
#include "ServerPacketHandler.h"
namespace W
{
	WInputPacket::WInputPacket():
		Packet(ePacketType::C_INPUT)
	{

	}
	WInputPacket::~WInputPacket()
	{
	}
	void WInputPacket::AddInput(const std::vector<UCHAR>& _vecInput)
	{
	}
}


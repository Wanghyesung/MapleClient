#pragma once
#include "WPacket.h"

namespace W
{
	class WInputPacket : public Packet
	{
	public:
		WInputPacket();
		virtual ~WInputPacket();


		void AddInput(const std::vector<UCHAR>& _vecInput);
	private:
		std::vector<UCHAR> m_vecInput; //�̹������� ��ǲ
	};
}


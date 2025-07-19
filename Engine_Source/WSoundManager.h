#pragma once
#include "WAudioClip.h"
#include "WRingBuffer.h"

namespace W
{
	class SoundManager
	{
	public:
		static void Update(); //사운드 스레드
		static void Push(weak_ptr<AudioClip> _wpAudioCclip);
		
	private:
		static RingBuffer<weak_ptr<AudioClip>, 50> m_RingBuffer;

		static atomic<bool> m_bEvent;
	};
}


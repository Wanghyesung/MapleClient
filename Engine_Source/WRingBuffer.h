#pragma once

#include "Engine.h"
namespace W
{
	/*
	SPSC(싱글 프로듀서·싱글 컨슈머):
	게임 스레드 하나가 “사운드 명령”만 푸시

	반면에, 패킷 처리나 이벤트 매니저는…

	멀티프로듀서(MP):
	네트워크 스레드, 물리 스레드, AI 스레드 등 여러 곳에서 “이벤트”를 큐에 넣음

	멀티컨슈머(MC):
	애	니메이션, 이펙트, UI, 사운드 등 여러 시스템이 동일 이벤트를 구독

	순간적으로 이벤트가 폭주할 수 있고, 버퍼 크기를 고정하기가 어려움
	*/
	template <typename T, size_t SIZE>
	class RingBuffer
	{
	public:
		static bool Push(T _pSound);
		static bool Pop(T& _pTarget);

		static bool IsFull() 
		{
			auto next = (m_iTail.load() + 1) % SIZE;
			return next == m_iHead.load();
		}

		static bool IsEmpty()
		{
			return m_iHead.load() == m_iTail.load();
		}
	private:
		static atomic<int> m_iHead;
		static atomic<int> m_iTail;
		
		static T m_Buffer[SIZE];
	};


	template<typename T, size_t SIZE>
	inline bool RingBuffer<T, SIZE>::Push(T _pSound)
	{
		size_t lTail = m_iTail.load();
		size_t iNext = (lTail + 1) % SIZE;
		if (iNext == m_iHead.load())
			return false;

		m_Buffer[lTail] = _pSound;

		m_iTail.store(iNext);

		return true;
	}

	template<typename T, size_t SIZE>
	inline bool RingBuffer<T, SIZE>::Pop(T& _pTarget)
	{
		size_t lHead = m_iHead.load();
		size_t iNext = (lHead + 1) % SIZE;
		if (lHead == m_iTail.load())
			return false;

		m_iHead.store(iNext);

		_pTarget = m_Buffer[lHead];
		return true;
	}


}

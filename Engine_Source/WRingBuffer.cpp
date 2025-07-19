#include "WRingBuffer.h"

namespace W
{
	template<typename T, size_t SIZE>
	std::atomic<int> RingBuffer<T, SIZE>::m_iHead{ 0 };
	template<typename T, size_t SIZE>
	std::atomic<int> RingBuffer<T, SIZE>::m_iTail{ 0 };
	template<typename T, size_t SIZE>
	T RingBuffer<T, SIZE>::m_Buffer[SIZE];
}
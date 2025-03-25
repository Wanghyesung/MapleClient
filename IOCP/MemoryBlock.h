#pragma once


class MemoryBlock
{
public:
	MemoryBlock(size_t _size, BYTE* _buffer, size_t _count);
	~MemoryBlock();

public:
	class MemoryHeader* Pop();
	void Push(MemoryHeader* _ptr);


private:
	size_t m_size;//내 사이즈
	size_t m_memoryCount; //몇개로 관리할지
	BYTE* m_Buffer;//메모리 풀에서 할당해준 내 버퍼

/*
연결 리스트 기반 스택/큐는 메모리 접근이 분산되어 캐시 친화적이지 않을 수 있음.
노드가 연속적인 메모리 공간에 배치되지 않기 때문. 배열 기반 스택/큐로 전환
캐시 히트율 증가.
메모리 접근 속도 향상.
*/
	RWLock m_Lock;
	vector<BYTE*> m_Memroy;//받은 바이트를 내 사이즈만큼 나눠서 보관
	MemoryPool* m_pOwner;


	friend class MemoryPool;
};


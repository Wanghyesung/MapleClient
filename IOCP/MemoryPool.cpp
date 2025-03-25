#include "pch.h"
#include "MemoryPool.h"
#include "MemoryBlock.h"

MemoryPool::MemoryPool():
	m_vecMemory{},
	m_Buffer{}
{
	int i = 1;

	BYTE* nextMemory = m_Buffer;
	m_vecMemory.resize(MAX_POOLING_SIZE + 1);

	MemoryBlock* memory32 = new MemoryBlock(32, nextMemory, COUNT_32);
	memory32->m_pOwner = this;
	for (i ; i <= 32; ++i)
	{
		m_vecMemory[i] = memory32;
	}
	nextMemory += COUNT_32 * 32;
	
	MemoryBlock* memory64 = new MemoryBlock(64, nextMemory, COUNT_64);
	memory64->m_pOwner = this;
	for (i; i <= 64; ++i)
	{
		m_vecMemory[i] = memory64;
	}
	nextMemory += (COUNT_64 * 64);
	
	
	MemoryBlock* memory128 = new MemoryBlock(128, nextMemory, COUNT_128);
	memory128->m_pOwner = this;
	for (i; i <= 128; ++i)
	{
		m_vecMemory[i] = memory128;
	}
	nextMemory += (COUNT_128 * 128);
	
	
	MemoryBlock* memory256 = new MemoryBlock(256, nextMemory, COUNT_256);
	memory256->m_pOwner = this;
	for (i; i <= 256; ++i)
	{
		m_vecMemory[i] = memory256;
	}
	nextMemory += (COUNT_256 * 256);
	
	
	MemoryBlock* memory512 = new MemoryBlock(512, nextMemory, COUNT_512);
	memory512->m_pOwner = this;
	for (i; i <= 512; ++i)
	{
		m_vecMemory[i] = memory512;
	}
	nextMemory += (COUNT_512 * 512);
	
	
	MemoryBlock* memory1024 = new MemoryBlock(1024, nextMemory, COUNT_1024);
	memory1024->m_pOwner = this;
	for (i; i <= 1024; ++i)
	{
		m_vecMemory[i] = memory1024;
	}
	nextMemory += (COUNT_1024 * 1024);
	
	
	MemoryBlock* memory2048 = new MemoryBlock(2048, nextMemory, COUNT_2048);
	memory2048->m_pOwner = this;
	for (i; i <= 2048; ++i)
	{
		m_vecMemory[i] = memory2048;
	}
	nextMemory += (COUNT_2048 * 2048);
}

MemoryPool::~MemoryPool()
{
	// 중복 해제를 방지하기 위해 set을 사용
	std::set<MemoryBlock*> setMemory;

	for (int i = 1; i <= MAX_POOLING_SIZE; ++i)
	{
		setMemory.insert(m_vecMemory[i]);
	}

	 for (MemoryBlock* pBlock : setMemory)
	 {
	 	delete pBlock;
		pBlock = nullptr;
	 }
	 
	 m_vecMemory.clear();
	 
	
}

MemoryHeader* MemoryPool::Pop(size_t _size)
{
	return  m_vecMemory[_size]->Pop();
}

void MemoryPool::Push(MemoryHeader* _ptr)
{
	m_vecMemory[_ptr->m_iSize]->Push(_ptr);
}

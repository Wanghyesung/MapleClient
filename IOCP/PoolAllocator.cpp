#include "pch.h"
#include "PoolAllocator.h"
#include "MemoryPool.h"


void* PoolAllocator::Alloc(size_t _size)
{
    MemoryHeader* pHeader = nullptr;
	int iTypeSize = _size + sizeof(MemoryHeader);

    if (_size > MAX_POOLING_SIZE)
        pHeader = reinterpret_cast<MemoryHeader*>(malloc(iTypeSize));
    else
        pHeader = MemoryPoolMgr->Pop(iTypeSize);


    return MemoryHeader::AttachHeader(pHeader, iTypeSize);
}

void PoolAllocator::Release(void* _ptr)
{
	MemoryHeader* pHeader = MemoryHeader::DetachHeader(_ptr);
	assert(pHeader->m_iSize > 0);

	if (pHeader->m_iSize > MAX_POOLING_SIZE)
	{
		free(_ptr);
	}
	else
	{
		MemoryPoolMgr->Push(pHeader);
		pHeader->m_iSize = 0;
	}
}

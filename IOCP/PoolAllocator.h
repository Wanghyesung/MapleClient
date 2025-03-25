#pragma once
class PoolAllocator
{
public:
	static void* Alloc(size_t _size);
	static void Release(void* _ptr);

};


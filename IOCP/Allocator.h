#pragma once
#include "PoolAllocator.h"

class MemoryHeader;
template<typename T, typename ...Args>
T* xnew(Args && ...args)
{
	void* pHeader = PoolAllocator::Alloc(sizeof(T));
	
	T* memory = static_cast<T*>(pHeader);
	new(memory)T(std::forward<Args>(args)...);
	return memory;
}

template<typename T>
void xdelete(T*& _ptr)
{
	_ptr->~T();

	PoolAllocator::Release(_ptr);

	_ptr = nullptr;
}

template<typename T, typename ...Args>
std::shared_ptr<T> MakeShared(Args && ...args)
{
	return std::shared_ptr<T>(xnew<T>(std::forward<Args>(args)...), xdelete<T>);
}


//template<typename T>
//class StlAllocator
//{
//public:
//	//stl value_type를 내 T타입으로
//	using value_type = T;
//
//
//	StlAllocator() {};
//
//	template<typename Other>
//	StlAllocator(const StlAllocator<Other>&) {};
//
//	//컨테이너 사이즈
//	T* allocate(size_t count)
//	{
//		int iSize = static_cast<int>(count * (sizeof(T)));
//		return static_cast<T*>(PoolAllocator::Alloc(iSize));
//	}
//
//	void deallocate(T* ptr, size_t count)
//	{
//		PoolAllocator::Release(ptr);
//	}
//};


#include "pch.h"
#include "Global.h"
#include "MemoryPool.h"
#include "SockHelper.h"
#include "ThreadManager.h"
#include "SendBufferChunk.h"

MemoryPool* MemoryPoolMgr= nullptr;
ThreadManager* ThreadMgr = nullptr;
SendBufferManager* SendBufferMgr = nullptr;
class Global
{
public:
	Global()
	{
		ThreadMgr = new ThreadManager();
		MemoryPoolMgr = new MemoryPool();
		SendBufferMgr = new SendBufferManager();
		SockHelper::init();
	}
	~Global()
	{
		delete ThreadMgr;
		delete MemoryPoolMgr;
		delete SendBufferMgr;
		SockHelper::Clear();
	}

}GGlobal;
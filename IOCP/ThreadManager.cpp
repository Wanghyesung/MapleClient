#include "pch.h"
#include "ThreadManager.h"
#include "GThread.h"


ThreadManager::ThreadManager()
{
	//main thread
	init();
}

ThreadManager::~ThreadManager()
{
	clear();
}


void ThreadManager::Excute(function<void(void)> _pFunc)
{
	lock_guard<mutex> lock(m_mutex);

	m_vecThread.push_back(thread([=]() {
		init();
		_pFunc();
		clear();
		}));

}

void ThreadManager::Join()
{
	for (int i = 0; i < m_vecThread.size(); ++i)
	{
		if (m_vecThread[i].joinable())
			m_vecThread[i].join();
	}

	m_vecThread.clear();
}

void ThreadManager::init()
{
	static atomic<int> atID = 1;

	T_Thread_ID = atID.fetch_add(1);
}

void ThreadManager::clear()
{
	//if (T_SendBufferChunk != nullptr)
	//{
	//	T_SendBufferChunk.reset();
	//}
}


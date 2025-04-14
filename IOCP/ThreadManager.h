#pragma once
#include <functional>


class ThreadManager
{

public:
	ThreadManager();
	~ThreadManager();

	void Excute(function<void(void)> _pFunc);
	void Join();

	static void init();
	static void clear();

private:
	vector<thread> m_vecThread;
	mutex m_mutex;
};


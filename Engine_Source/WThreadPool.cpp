#include "WThreadPool.h"

namespace W
{
	std::vector<std::thread> ThreadPool::m_vecWorker = {};
	std::queue<std::function<void()>> ThreadPool::m_queueTasks = {};

	std::mutex ThreadPool::m_mutex = {};
	std::condition_variable ThreadPool::m_CV = {};
	std::atomic<bool> ThreadPool::m_bRunnig = true;

	std::mutex ThreadPool::m_completeMutex = {};
	std::condition_variable ThreadPool::m_completeCV = {};
	std::atomic<int> ThreadPool::m_iWorkCount = 0;

	void ThreadPool::Initiailize(int _iThreadCount)
	{
		for (int i = 0; i < _iThreadCount; ++i)
		{
			//std::thread는 복사 생성자가 delete 되어 있어서 복사 불가능
			m_vecWorker.emplace_back([]() {
				while (true)
				{
					std::function<void()> funcTask;
					{
						std::unique_lock<std::mutex> lock(m_mutex);
						m_CV.wait(lock, []() {return !m_bRunnig || !m_queueTasks.empty(); });

						if (!m_bRunnig)
							return;

						funcTask = std::move(m_queueTasks.front());
						m_queueTasks.pop();
					}
					funcTask();

					m_iWorkCount.fetch_sub(1);

					if (m_iWorkCount.load() == 0)
						m_completeCV.notify_one();
				}
			});
		}
	}
	void ThreadPool::Shutdown()
	{
		m_bRunnig.store(false);
	
		m_CV.notify_all();

		for (int i = 0; i < m_vecWorker.size(); ++i)
		{
			if (m_vecWorker[i].joinable())
				m_vecWorker[i].join();
		}

		m_vecWorker.clear();
	}

	void ThreadPool::Enqueu(std::function<void()> _func)
	{
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_queueTasks.push(_func);
		}

		m_iWorkCount.fetch_add(1);
		m_CV.notify_one();
	}

	void ThreadPool::Joinable()
	{
		std::unique_lock<std::mutex> lock(m_completeMutex);
		m_completeCV.wait(lock, []() {return m_iWorkCount.load() == 0; });

	}
	
}
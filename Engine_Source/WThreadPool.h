#pragma once

#include "Engine.h"
#include "WResources.h"

namespace W
{
	class ThreadPool
	{
	public:
		static void Initiailize(int _iThreadCount);
		static void Shutdown();

		static void Enqueu(std::function<void()> _func);

		template <typename T>
		static void LoadingResource(const std::wstring& _strResourceName , const std::wstring& _strPath);
		template <typename T>
		static void DeleteResource(const std::wstring& _strResourceName);

		static void Joinable(); //블로킹 함수

	private:
		static std::vector<std::thread> m_vecWorker;
		static std::queue<std::function<void()>> m_queueTasks;

		static std::mutex m_mutex;
		static std::condition_variable m_CV;//작업 스레드 깨우기용
		static std::atomic<bool> m_bRunnig;

		static std::mutex m_completeMutex; //외부 대기 스레드용
		static std::condition_variable m_completeCV;
		static std::atomic<int> m_iWorkCount;
	};
	template<typename T>
	inline void ThreadPool::LoadingResource(const std::wstring& _strResourceName, const std::wstring& _strPath)
	{
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_queueTasks.push([=]()
				{
					//template에서 template함수 호출시 template 명시
					Resources::template Load<T>(_strResourceName, _strPath);
				});
		}
		m_iWorkCount.fetch_add(1);
		m_CV.notify_all();	
	}
	template<typename T>
	inline void ThreadPool::DeleteResource(const std::wstring& _strResourceName)
	{
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_queueTasks.push([=]()
				{
					//template에서 template함수 호출시 template 명시
					Resources::template Release<T>(_strResourceName);
				});
		}
		m_iWorkCount.fetch_add(1);
		m_CV.notify_all();
	}
}

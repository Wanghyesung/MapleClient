#include "WObjectPoolManager.h"
#include "WGameObject.h"


namespace W
{
	std::unordered_map<std::wstring, std::queue<GameObject*>> ObjectPoolManager::m_hashObjectPool = {};

	void ObjectPoolManager::AddObjectPool(const std::wstring& _strName, GameObject* _pGameObj)
	{
		std::unordered_map<std::wstring, std::queue<GameObject*>>::iterator iter =
			m_hashObjectPool.find(_strName);

		if (iter == m_hashObjectPool.end())
		{
			std::queue<GameObject*> queue = {};
			m_hashObjectPool.insert(std::make_pair(_strName, queue));
		}

		m_hashObjectPool[_strName].push(_pGameObj);
	}
	GameObject* ObjectPoolManager::FrontObject(const std::wstring& _strName)
	{
		std::unordered_map<std::wstring, std::queue<GameObject*>>::iterator iter =
			m_hashObjectPool.find(_strName);

		if (iter != m_hashObjectPool.end())
		{
			std::queue<GameObject*>& queue = m_hashObjectPool[_strName];

			if (!queue.empty())
			{
				GameObject* pGameObj = queue.front();
				queue.pop();

				return pGameObj;
			}
		}
		return nullptr;
	}

	void ObjectPoolManager::Release()
	{
		std::unordered_map<std::wstring, std::queue<GameObject*>>::iterator iter =
			m_hashObjectPool.begin();

		for (iter; iter != m_hashObjectPool.end(); ++iter)
		{
			std::queue<GameObject*> queue = iter->second;
			while (!queue.empty())
			{
				GameObject* pGameObj = queue.front();
				queue.pop();

				delete pGameObj;
				pGameObj = nullptr;
			}
		}
	}

	void ObjectPoolManager::ReleaseObject(const std::wstring& _strName)
	{
		std::unordered_map<std::wstring, std::queue<GameObject*>>::iterator iter =
			m_hashObjectPool.find(_strName);

		if (iter == m_hashObjectPool.end())
			return;

		std::queue<GameObject*>& queue = iter->second;
		while (!queue.empty())
		{
			GameObject* pGameObj = queue.front();
			queue.pop();

			delete pGameObj;
			pGameObj = nullptr;
		}

		m_hashObjectPool.erase(_strName);
	}

}



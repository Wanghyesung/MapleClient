#include "WObjectPoolManager.h"
#include "WGameObject.h"
#include "WAnimator.h"

namespace W
{
	std::unordered_map<std::wstring, std::vector<GameObject*>> ObjectPoolManager::m_hashObjectPool = {};

	void ObjectPoolManager::AddObjectPool(const std::wstring& _strName, GameObject* _pGameObj)
	{
		std::unordered_map<std::wstring, std::vector<GameObject*>>::iterator iter =
			m_hashObjectPool.find(_strName);

		if (iter == m_hashObjectPool.end())
		{
			std::vector<GameObject*> vec = {};
			m_hashObjectPool.insert(std::make_pair(_strName, vec));
		}

		m_hashObjectPool[_strName].push_back(_pGameObj);

		_pGameObj->SetPoolObject(true);
	}
	GameObject* ObjectPoolManager::PopObject(const std::wstring& _strName)
	{
		std::unordered_map<std::wstring, std::vector<GameObject*>>::iterator iter =
			m_hashObjectPool.find(_strName);

		if (iter != m_hashObjectPool.end())
		{
			std::vector<GameObject*>& vec = m_hashObjectPool[_strName];

			if (!vec.empty())
			{
				GameObject* pGameObj = vec.back();
				vec.pop_back();

				return pGameObj;
			}
		}
		return nullptr;
	}

	void ObjectPoolManager::Release()
	{
		std::unordered_map<std::wstring, std::vector<GameObject*>>::iterator iter =
			m_hashObjectPool.begin();

		for (iter; iter != m_hashObjectPool.end(); ++iter)
		{
			std::vector<GameObject*>& vec = iter->second;
			for (int i = 0; i < vec.size(); ++i)
			{
				delete vec[i];
				vec[i] = nullptr;
			}
			vec.clear();
		}
	}

	void ObjectPoolManager::ReleaseObject(const std::wstring& _strName)
	{
		std::unordered_map<std::wstring, std::vector<GameObject*>>::iterator iter =
			m_hashObjectPool.find(_strName);

		if (iter == m_hashObjectPool.end())
			return;

		std::vector<GameObject*>& vec = iter->second;
		for (int i = 0; i < vec.size(); ++i)
		{
			delete vec[i];
			vec[i] = nullptr;
		}

		m_hashObjectPool.erase(_strName);
	}

	const std::vector<GameObject*>& ObjectPoolManager::GetObejcts(const wstring& _strName)
	{
		std::unordered_map<std::wstring, std::vector<GameObject*>>::iterator iter =
			m_hashObjectPool.find(_strName);

		if (iter == m_hashObjectPool.end())
			return {};

		return iter->second;
	}

	

}



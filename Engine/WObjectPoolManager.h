#pragma once

#include "Engine.h"

namespace W
{
	class GameObject;
	
	class ObjectPoolManager
	{
	public:
		static void AddObjectPool(const std::wstring& _strName, GameObject* _pGameObj);
		static GameObject* FrontObject(const std::wstring& _strName);
		
		static void Release();
		static void ReleaseObject(const std::wstring& _strName);
	private:
		static std::unordered_map<std::wstring, std::queue<GameObject*>> m_hashObjectPool;

	};
}


#pragma once

#include "..\Engine_Source\Engine.h"


namespace W
{
	class GameObject;
	class Texture;
	class ObjectPoolManager
	{
	public:

		static void AddObjectPool(const std::wstring& _strName, GameObject* _pGameObj);
		static GameObject* PopObject(const std::wstring& _strName);
		
		static void Release();
		static void ReleaseObject(const std::wstring& _strName);

		static const std::vector<GameObject*>& GetObejcts(const wstring& _strName);
	private:
		static std::unordered_map<std::wstring, std::vector<GameObject*>> m_hashObjectPool;

	};
}


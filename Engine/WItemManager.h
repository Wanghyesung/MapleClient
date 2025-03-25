#pragma once
#include "Engine.h"
#include "WIconUI.h"
namespace W
{
	class ItemManager
	{
	public:
		static void Initialize();
		static void Release();

		static void AddItem(IconUI* pItem);
		static IconUI* GetClone(const std::wstring& _strName);
	private:
		static IconUI* find_item(const std::wstring& _strName);

		static void chanage_hair();
		static void chanage_eye();
	private:
		static std::unordered_map<std::wstring, IconUI*> m_hashItems;
	};
}



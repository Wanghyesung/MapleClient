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

		static void AddItem(IconUI* _pItem);
		static IconUI* GetClone(const wstring& _strName);
		static IconUI* GetItem(UINT _iID);
		static const wstring& GetItemName(UINT _iID);
		static int GetItemID(const wstring& _strName);

	private:
		static void initialize_factory();

		static IconUI* find_item(const wstring& _strItemName);

		static void chanage_hair();
		static void chanage_eye();



	private:
		static map<wstring, IconUI*> m_mapItems;
		static map<UINT, wstring> m_mapItemID;

		static unordered_map<string, function<IconUI*()>> m_hashItemFactory;
	};
}



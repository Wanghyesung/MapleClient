#include "WItemManager.h"
#include "WAlixirUI.h"
#include "WHorntailItem.h"
#include "WHairItem.h"
#include "WEyeItem.h"
#include "WWeapon_10.h"
#include "WHat_10.h"
#include "WTop_10.h"
#include "WBottom_10.h"
#include "WShoes_10.h"
#include "WWeapon_25.h"
#include "WHat_40.h"
#include "WTop_40.h"
#include "WBottom_40.h"
#include "WShoes_40.h"
#include "WWeapon_63.h"
#include "WHat_80.h"
#include "WTop_80.h"
#include "WBottom_80.h"
#include "WShoes_80.h"
#include "WPlayer.h"
#include "WSceneManger.h"

namespace W
{
#define HashItems std::unordered_map<std::wstring, IconUI*>

	HashItems ItemManager::m_hashItems = {};
	void ItemManager::Initialize()
	{
		//아이템 텍스쳐, 객체 이름, 보관이름 전부 동일하게
#pragma region Item
		AlixirUI* pAlixir = new AlixirUI();
		pAlixir->Initialize();
		pAlixir->SetName(L"alixir");
		AddItem(pAlixir);

		HairItem* pHairItem = new HairItem();
		pHairItem->Initialize();
		pHairItem->SetFunction(ItemManager::chanage_hair);
		pHairItem->SetName(L"hairitem");
		AddItem(pHairItem);

		EyeItem* pEyeItem = new EyeItem();
		pEyeItem->Initialize();
		pEyeItem->SetFunction(ItemManager::chanage_eye);
		pEyeItem->SetName(L"eyeitem");
		AddItem(pEyeItem);

		HorntailItem* pHorntailItem = new HorntailItem();
		pHorntailItem->SetName(L"horntailItem");
		AddItem(pHorntailItem);

		Weapon_10* pWeapon10 = new Weapon_10();
		pWeapon10->SetName(L"10_weapon");
		AddItem(pWeapon10);

		Hat_10* pHat10 = new Hat_10();
		pHat10->SetName(L"10_hat");
		AddItem(pHat10);

		Top_10* pTop10 = new Top_10();
		pTop10->SetName(L"10_top");
		AddItem(pTop10);

		Bottom_10* pBottom10 = new Bottom_10();
		pBottom10->SetName(L"10_bottom");
		AddItem(pBottom10);

		Shoes_10* pShoes10 = new Shoes_10();
		pShoes10->SetName(L"10_shoes");
		AddItem(pShoes10);

		Weapon_25* pWeapon25 = new Weapon_25();
		pWeapon25->SetName(L"25_weapon");
		AddItem(pWeapon25);

		Hat_40* pHat40 = new Hat_40();
		pHat40->SetName(L"40_hat");
		AddItem(pHat40);

		Top_40* pTop40 = new Top_40();
		pTop40->SetName(L"40_top");
		AddItem(pTop40);

		Bottom_40* pBottom40 = new Bottom_40();
		pBottom40->SetName(L"40_bottom");
		AddItem(pBottom40);

		Shoes_40* pShoes40 = new Shoes_40();
		pShoes40->SetName(L"40_shoes");
		AddItem(pShoes40);

		Hat_80* pHat80 = new Hat_80();
		pHat80->SetName(L"80_hat");
		AddItem(pHat80);

		Top_80* pTop80 = new Top_80();
		pTop80->SetName(L"80_top");
		AddItem(pTop80);

		Bottom_80* pBottom80 = new Bottom_80();
		pBottom80->SetName(L"80_bottom");
		AddItem(pBottom80);

		Shoes_80* pShoes80 = new Shoes_80();
		pShoes80->SetName(L"80_shoes");
		AddItem(pShoes80);

		Weapon_63* pWeapon63 = new Weapon_63();
		pWeapon63->SetName(L"63_weapon");
		AddItem(pWeapon63);
#pragma endregion

	}
	void ItemManager::Release()
	{
		HashItems::iterator iter = m_hashItems.begin();

		for (iter; iter != m_hashItems.end(); ++iter)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
	void ItemManager::AddItem(IconUI* pItem)
	{
		const IconUI* pIcon = find_item(pItem->GetName());
		if (pIcon != nullptr)
			return;

		m_hashItems.insert(std::make_pair(pItem->GetName(), pItem));
	}
	IconUI* ItemManager::find_item(const std::wstring& _strName)
	{
		HashItems::iterator iter =
			m_hashItems.find(_strName);

		if (iter == m_hashItems.end())
			return nullptr;
		
		return iter->second;
	}
	void ItemManager::chanage_hair()
	{
		std::random_device rDiv;
		std::mt19937 en(rDiv());
		std::uniform_int_distribution<int> disX(0, 1);
		int iHairNum = disX(en);
		//임시
		iHairNum = 1;
		dynamic_cast<Player*>(SceneManger::FindPlayer())->SetHair(iHairNum);
	}
	void ItemManager::chanage_eye()
	{
		std::random_device rDiv;
		std::mt19937 en(rDiv());
		std::uniform_int_distribution<int> disX(0, 2);
		int iEyeNum = disX(en);

		//임시
		iEyeNum = 1;
		dynamic_cast<Player*>(SceneManger::FindPlayer())->SetEye(iEyeNum);
	}
	IconUI* ItemManager::GetClone(const std::wstring& _strName)
	{
		IconUI* pIcon = find_item(_strName);

		if (pIcon == nullptr)
			return nullptr;

		return pIcon->Create_Clone();
	}


}
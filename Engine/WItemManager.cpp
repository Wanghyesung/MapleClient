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

#include "WPathManager.h"
#include <nlohmann/json.hpp>

namespace W
{
	using json = nlohmann::json;

	map<wstring, IconUI*> ItemManager::m_mapItems = {};
	map<UINT, wstring> ItemManager::m_mapItemID = {};
	unordered_map<string, function<IconUI*()>> ItemManager::m_hashItemFactory = {};
	vector<std::function<void(UINT, UINT)>> ItemManager::m_vecItemEvent = {};

	void ItemManager::Initialize()
	{
		initialize_factory();
		initialize_function();

		unordered_map<string, UINT> hashItem =
		{
			{"Equip", (UINT)IconUI::eIconType::Equip},
			{"Item", (UINT)IconUI::eIconType::Item},
			{"Install", (UINT)IconUI::eIconType::Install},
			{"Cash", (UINT)IconUI::eIconType::Cash},
			{"Another", (UINT)IconUI::eIconType::Another},
			{"SKill", (UINT)IconUI::eIconType::SKill},

		};

		wstring strPath = PathManager::GetContentPath();
		strPath += L"\\Resources\\GameData\\Item.json";

		std::ifstream ifs(strPath.c_str());
		if (!ifs.is_open())
			assert(nullptr);

		json jFile;
		ifs >> jFile;

		for (auto& jData : jFile.at("items"))
		{
			const string& strItemName = jData.at("name").get<std::string>();
			const string& strClassName = jData.at("class").get<std::string>();

			IconUI* pItem = m_hashItemFactory[strClassName]();

			pItem->m_iItemID = jData.at("id").get<uint32_t>();
			pItem->m_iItemLevel = jData.at("level").get<uint32_t>();
			pItem->m_eType = (IconUI::eIconType)hashItem[jData.at("iconType").get<std::string>()];
			pItem->Initialize();
			pItem->SetName(StringToWString(strItemName));
			AddItem(pItem);

			m_mapItemID.insert(make_pair(pItem->m_iItemID, StringToWString(strItemName)));
		}
	}
	void ItemManager::Release()
	{
		auto iter = m_mapItems.begin();
		for (iter; iter != m_mapItems.end(); ++iter)
		{
			delete iter->second;
			iter->second = nullptr;
		}

	}
	void ItemManager::AddItem(IconUI* _pItem)
	{
		IconUI* pIcon = find_item(_pItem->GetName());
		if (pIcon != nullptr)
			return;

		m_mapItems.insert(std::make_pair(_pItem->GetName(), _pItem));
	}

	int ItemManager::GetItemID(const wstring& _strName)
	{
		IconUI* pIcon = find_item(_strName);
		if (pIcon == nullptr)
			return -1;
	
		return pIcon->m_iItemID;
	}

	void ItemManager::ExcuteItem(UINT _iFuncInfo, UINT _iItemValue)
	{
		USHORT sFuncID = _iFuncInfo & 0xFFFF;
		UCHAR cPlayerID = (_iFuncInfo >> 16) & 0xFF;

		m_vecItemEvent[sFuncID](cPlayerID, _iItemValue);
	}

	IconUI* ItemManager::find_item(const wstring& _strItemName)
	{
		auto iter = m_mapItems.find(_strItemName);
	
		if (iter == m_mapItems.end())
			return nullptr;
		
		return iter->second;
	}

	void ItemManager::chanage_hair(UINT _iPlayerID, UINT _iPlayerValue)
	{
		GameObject* pObj = SceneManger::FindObject(_iPlayerID, eLayerType::Player);
		if (pObj)
		{
			Player* pPlayer = static_cast<Player*>(pObj);
			pPlayer->SetHair(_iPlayerValue);
		}
	}

	void ItemManager::chanage_eye(UINT _iPlayerID, UINT _iPlayerValue)
	{
		GameObject* pObj = SceneManger::FindObject(_iPlayerID, eLayerType::Player);
		if (pObj)
		{
			Player* pPlayer = static_cast<Player*>(pObj);
			pPlayer->SetEye(_iPlayerValue);
		}
	}

	IconUI* ItemManager::GetClone(const wstring& _strName)
	{
		auto iter = m_mapItems.find(_strName);
		if (iter == m_mapItems.end())
			return nullptr;

		return iter->second->Create_Clone();
	}

	IconUI* ItemManager::GetItem(UINT _iID)
	{
		auto iter = m_mapItemID.find(_iID);
		if (iter == m_mapItemID.end())
			return nullptr;
	
		auto itemIter = m_mapItems.find(iter->second);
		if (itemIter != m_mapItems.end())
			return itemIter->second;
	}

	const wstring& ItemManager::GetItemName(UINT _iID)
	{
		auto iter = m_mapItemID.find(_iID);
		if (iter == m_mapItemID.end())
			return {};
	
		return iter->second;
	}


	void ItemManager::initialize_factory()
	{
		m_hashItemFactory["AlixirUI"] = []() {return new AlixirUI(); };
		m_hashItemFactory["HairItem"] = []() {return new HairItem(); };
		m_hashItemFactory["EyeItem"] = []() {return new EyeItem(); };
		m_hashItemFactory["HorntailItem"] = []() {return new HorntailItem(); };
		m_hashItemFactory["Hat_10"] = []() {return new Hat_10(); };
		m_hashItemFactory["Top_10"] = []() {return new Top_10(); };
		m_hashItemFactory["Weapon_10"] = []() {return new Weapon_10(); };
		m_hashItemFactory["Bottom_10"] = []() {return new Bottom_10(); };
		m_hashItemFactory["Shoes_10"] = []() {return new Shoes_10(); };
		m_hashItemFactory["Weapon_25"] = []() {return new Weapon_25(); };
		m_hashItemFactory["Hat_40"] = []() {return new Hat_40(); };
		m_hashItemFactory["Top_40"] = []() {return new Top_40(); };
		m_hashItemFactory["Bottom_40"] = []() {return new Bottom_40(); };
		m_hashItemFactory["Shoes_40"] = []() {return new Shoes_40(); };
		m_hashItemFactory["Hat_80"] = []() {return new Hat_80(); };
		m_hashItemFactory["Top_80"] = []() {return new Top_80(); };
		m_hashItemFactory["Bottom_80"] = []() {return new Bottom_80(); };
		m_hashItemFactory["Shoes_80"] = []() {return new Shoes_80(); };
		m_hashItemFactory["Weapon_63"] = []() {return new Weapon_63(); };
	}

	void ItemManager::initialize_function()
	{
		m_vecItemEvent.resize(20);

		//ID = Function;
		m_vecItemEvent[1] = chanage_hair;
		m_vecItemEvent[2] = chanage_eye;
	}


}
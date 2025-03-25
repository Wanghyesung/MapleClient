#include "WInventory.h"
#include "WAlixirUI.h"
#include "WTransform.h"
#include "WAlixirUI.h"
#include "WSceneManger.h"
#include "WInput.h"
#include "WScroll.h"
#include "WHorntailItem.h"
#include "WInterfaceUI.h"
#include "WInvenPage.h"
#include "WHat_10.h"
#include "WTop_10.h"
#include "WBottom_10.h"
#include "WShoes_10.h"
#include "WWeapon_10.h"
#include "WObject.h"
#include "WItemManager.h"
namespace W
{
	Inventory::Inventory():
		m_bRenderOn(false),
		m_mapItems{},
		m_vecPages{},
		m_vUIStartPosition(Vector2::One),
		m_vUIEndPosition(Vector2::One),
		m_vUIDiffPosition(Vector2::One),
		m_eActivePage(eItemPage::Equip),
		m_pScroll(nullptr),
		m_iScrollCurY(0)
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"Inven0Tex", L"..\\Resources\\Texture\\UI\\InvenUI\\Inven0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		//pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"Inven0Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}

	Inventory::~Inventory()
	{

	}

	void Inventory::Initialize()
	{
		Transform* pTransform = GetComponent<Transform>();
		pTransform->SetPosition(0.f, 0.f, -5.f);
		pTransform->SetScale(0.518f * 3.8f, 1.f * 3.8f, 0.f); //0.518 : 1

		m_vUIStartPosition = Vector2(-0.68f, 1.2f);
		m_vUIEndPosition = Vector2(0.58f, -0.9f);
		m_vUIDiffPosition = Vector2(0.42f, -0.42f);
		

#pragma region Items
		//받을 떄 itemui까지만 복사생성자를 만들어서 상속이 itemui까지만 감
		IconUI* pAlxir = ItemManager::GetClone(L"alixir");
		AddItem(pAlxir, pAlxir->GetName());

		IconUI* phair = ItemManager::GetClone(L"hairitem");
		AddItem(phair, phair->GetName());

		IconUI* pEye = ItemManager::GetClone(L"eyeitem");
		AddItem(pEye, pEye->GetName());

		IconUI* pHorn = ItemManager::GetClone(L"horntailItem");
		AddItem(pHorn, pHorn->GetName());

		IconUI* pWeapon = ItemManager::GetClone(L"10_weapon");
		AddItem(pWeapon, pWeapon->GetName());

		//IconUI* pEquip = ItemManager::GetClone(L"25_weapon");
		//AddItem(pEquip, pEquip->GetName());

		IconUI* pEquip = ItemManager::GetClone(L"40_hat");
		AddItem(pEquip, pEquip->GetName());

		pEquip = ItemManager::GetClone(L"40_bottom");
		AddItem(pEquip, pEquip->GetName());

		pEquip = ItemManager::GetClone(L"40_top");
		AddItem(pEquip, pEquip->GetName());

		pEquip = ItemManager::GetClone(L"40_shoes");
		AddItem(pEquip, pEquip->GetName());

		pEquip = ItemManager::GetClone(L"63_weapon");
		AddItem(pEquip, pEquip->GetName());

		pEquip = ItemManager::GetClone(L"80_hat");
		AddItem(pEquip, pEquip->GetName());

		pEquip = ItemManager::GetClone(L"80_bottom");
		AddItem(pEquip, pEquip->GetName());

		pEquip = ItemManager::GetClone(L"80_top");
		AddItem(pEquip, pEquip->GetName());

		pEquip = ItemManager::GetClone(L"80_shoes");
		AddItem(pEquip, pEquip->GetName());
		
#pragma endregion

		//page 초기화
		Vector3 vPosition = Vector3(-0.7f, 1.55f, 0.f);
		for (UINT i = 0; i <(UINT)eItemPage::End; ++i)
		{
			InvenPage* pInvenPage = new InvenPage((eItemPage)i);
			pInvenPage->GetComponent<Transform>()->SetPosition(vPosition); //1.526 : 1 -2.03 1.78 
			pInvenPage->GetComponent<Transform>()->SetScale(0.1526f * 2.1f, 0.1f * 1.8f, 0.f);
			AddChildUI(pInvenPage, false);
			pInvenPage->Initialize();
			vPosition.x += 0.35f;
			m_vecPages.push_back(pInvenPage);
		}

		m_pScroll = new Scroll();
		AddChildUI(m_pScroll);
		m_pScroll->Initialize();
		m_pScroll->SetMaxY(4);
		m_pScroll->SetEndPosition(Vector2(0.f, -0.8f));
		m_pScroll->SetParntUI(eParentUI::Inventory);

		//현재 볼 아이템
		SetActivePage(eItemPage::Equip);
	}
	void Inventory::Update()
	{
		if (!m_bRenderOn)
			return;

		

		UI::Update();
	}
	void Inventory::LateUpdate()
	{
		if (!m_bRenderOn)
			return;

		UI::LateUpdate();
	}
	void Inventory::Render()
	{
		if (!m_bRenderOn)
			return;

		UI::Render();
	}
	void Inventory::MouseOn()
	{
		if (m_bTargetOn)
		{
			Transform* pTransform = GetComponent<Transform>();
			Vector2 vMousePos = Input::GetMousePos();

			Vector2 vDiff = vMousePos - m_vDragStartPos;
			Vector3 vPosisition = pTransform->GetPosition() + vDiff;

			pTransform->SetPosition(vPosisition);

			MoveToParent(vDiff);

			m_vDragStartPos = Input::GetMousePos();
		}

	}
	void Inventory::MouseLbtnDown()
	{
		m_bTargetOn = true;

		m_vDragStartPos = Input::GetMousePos();

	}
	void Inventory::MouseLbtnUp()
	{
		m_bTargetOn = false;

		//m_vUIEndPosition = Input::GetMousePos();
	}

	void Inventory::MouseLbtnClicked()
	{

	}

	IconUI* Inventory::FindItem(std::wstring _strName)
	{
		std::map<std::wstring, IconUI*>::iterator iter = m_mapItems.find(_strName);

		if (iter == m_mapItems.end())
			return nullptr;

		return iter->second;
	}
	void Inventory::InsertItem(IconUI* _pItem, std::wstring _strName)
	{
		AddChildUI(_pItem, false);

		m_mapItems.insert(make_pair(_strName, _pItem));

		_pItem->SetParentUIType(eParentUI::Inventory);
	}

	void Inventory::AddItem(IconUI* _pItem , std::wstring _strName)
	{
		//-3.6 -0.8
		//내 인터페이스랑 인벤토리 둘다 확인
		bool bClear = false;
		IconUI* pItem = FindItem(_strName);
		IconUI* pInterfaceItem = SceneManger::GetUI<InterfaceUI>()->FindItem(_strName);
		if (pItem != nullptr)
		{
			dynamic_cast<ItemUI*>(pItem)->AddItemNumber(1);
			bClear = true;
		}
		else if (pInterfaceItem != nullptr)
		{
			dynamic_cast<ItemUI*>(pInterfaceItem)->AddItemNumber(1);
			bClear = true;
		}
		if (bClear)
		{
			delete _pItem;
			_pItem = nullptr;
			return;
		}


		//새로운 아이템
		if (SetItemPosition(_pItem))
		{
			AddChildUI(_pItem, false);
			_pItem->Initialize();
			//새로운 이름으로 초기화(중복아이템 이름 겹치지않게)
			std::wstring strName = _pItem->GetName();
			m_mapItems.insert(make_pair(strName, _pItem));
			_pItem->SetParentUIType(eParentUI::Inventory);
		}
		
	}

	bool Inventory::SetItemPosition(IconUI* _pItem)
	{
		//3.66 0.9 //3.2 0.45
		//인벤토리 위치
		Transform* pTransform = GetComponent<Transform>();
		Vector3 vPosition = pTransform->GetPosition();
		
		Transform* PItemTranform = _pItem->GetComponent<Transform>();
		Vector3 vItemPosition = PItemTranform->GetPosition();

		//비교할 벡터
		Vector2 vComaprePos = {};

		//1 : 1시작점
		Vector2 vStartPosition = Vector2(m_vUIStartPosition.x + vPosition.x, m_vUIStartPosition.y + vPosition.y);
		for (UINT y = 0; y < 10; ++y)
		{
			vComaprePos.y = vStartPosition.y + y * m_vUIDiffPosition.y;
			for (UINT x = 0; x < 4; ++x)
			{
				vComaprePos.x = vStartPosition.x + x * m_vUIDiffPosition.x;
				std::map<std::wstring, IconUI*>::iterator iter = m_mapItems.begin();
				
				//처음 들어온 아이템이라면
				if (iter == m_mapItems.end())
				{
					PItemTranform->SetPosition(vComaprePos.x, vComaprePos.y, vItemPosition.z);
					_pItem->SetItemIndex(x, y);
					return true;
				}

				IconUI* pITem = FindItemOnPosition(x, y, _pItem);
				//빈칸
				if (pITem == nullptr)
				{
					PItemTranform->SetPosition(vComaprePos.x, vComaprePos.y, vItemPosition.z);
					_pItem->SetItemIndex(x, y);
					return true;
				}
			}
		}


		return false;
	}

	bool Inventory::ChangeItemPosition(IconUI* _pItem, Vector2 _vSetPosition)
	{	
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		Transform* pItemTransform = _pItem->GetComponent<Transform>();

		Vector2 vStartPosition = Vector2(m_vUIStartPosition.x + vPosition.x, m_vUIStartPosition.y + vPosition.y);
		Vector2 vComaprePos = {};

		Vector2 vMinValue = Vector2(2000.f, 2000.f); 
		float fMinLen = 2000.f;
		UINT iMinX = 0; 
        UINT iMinY = 0;

		for (UINT y = 0; y < 6; ++y)
		{
			vComaprePos.y = vStartPosition.y + y * m_vUIDiffPosition.y;
			for (UINT x = 0; x < 4; ++x)
			{
				vComaprePos.x = vStartPosition.x + x * m_vUIDiffPosition.x;

				Vector2 vDiff = _vSetPosition - vComaprePos;
				float fLen = abs(vDiff.Length());

				if (fLen <= fMinLen)
				{
					fMinLen = fLen;
					vMinValue = vComaprePos;
					iMinX = x;
					iMinY = y;
				}
			}
		}

		
		iMinY += m_iScrollCurY;
		IconUI* pFindItem = FindItemOnPosition(iMinX, iMinY, _pItem);

		Vector3 vItemPosition = pItemTransform->GetPosition();
		
		if (_pItem->GetParentUIType() != eParentUI::Inventory)
		{
			if (pFindItem != nullptr)
			{
				eParentUI eParentType = _pItem->GetParentUIType();
				switch (eParentType)
				{
				case W::enums::eParentUI::Interface:
				{
					if (pFindItem->GetIconType() == IconUI::eIconType::Equip)
						return false;
					pFindItem->GetComponent<Transform>()->SetPosition(_pItem->GetStartPosition());
					pFindItem->SetItemIndex(_pItem->GetItemindexX(), _pItem->GetItemIndexY());
					pFindItem->DeleteParent();
					SceneManger::GetUI<InterfaceUI>()->InsertItem(pFindItem, pFindItem->GetName());
				}
				break;
				case W::enums::eParentUI::EquipState:
					return false;
				break;
				}
			}
			pItemTransform->SetPosition(vMinValue.x, vMinValue.y, vItemPosition.z);
			_pItem->SetItemIndex(iMinX, iMinY);
			_pItem->DeleteParent();
			InsertItem(_pItem, _pItem->GetName());
		}

		else
		{
			if (pFindItem != nullptr)
			{
				Transform* pFItemTr = pFindItem->GetComponent<Transform>();
				Vector3 vFItemPos = pFItemTr->GetPosition();

				Vector3 vItemStartPos = _pItem->GetStartPosition();
				int x = _pItem->GetItemindexX();
				int y = _pItem->GetItemIndexY();
				pFindItem->SetItemIndex(x, y);
				pFItemTr->SetPosition(vItemStartPos);
			}

			pItemTransform->SetPosition(vMinValue.x, vMinValue.y, vItemPosition.z);
			_pItem->SetItemIndex(iMinX, iMinY);
		}

		return true;
	}

	IconUI* Inventory::FindItemOnPosition(UINT _iX, UINT _iY, IconUI* _pIcon)
	{
		IconUI::eIconType eIconType = _pIcon->GetIconType();
		std::map<std::wstring, IconUI*>::iterator iter = m_mapItems.begin();

		for (iter; iter != m_mapItems.end(); ++iter)
		{
			IconUI* pITem = iter->second;
			UINT ITEM_X = pITem->GetItemindexX();
			UINT ITEM_Y = pITem->GetItemIndexY();

			//빈칸
			if (ITEM_X == _iX && ITEM_Y == _iY)
			{
				IconUI* pIcon = iter->second;

				if (pIcon->GetIconType() == eIconType)
					return pIcon;
			}
		}

		return nullptr;
	}

	void Inventory::SetActivePage(eItemPage _ePageType)
	{
		m_eActivePage = _ePageType; 
		for (UINT i = 0; i < (UINT)eItemPage::End; ++i)
		{
			if (m_eActivePage == (eItemPage)i)
				m_vecPages[i]->SetActive(true);
			else
				m_vecPages[i]->SetActive(false);
		}
	}
	bool Inventory::IsActivePage(UINT _i)
	{
		return m_vecPages[_i]->IsActive();
	}

	void Inventory::CheckPosition(int _iDir)
	{
		std::map<std::wstring, IconUI*>::iterator iter = m_mapItems.begin();
		for (iter; iter != m_mapItems.end(); ++iter)
		{
			iter->second->CheckPosition(_iDir, m_vUIDiffPosition);
		}
	}
}
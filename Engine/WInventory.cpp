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

		UI::MouseLbtnDown();
	}
	void Inventory::MouseLbtnUp()
	{
		m_bTargetOn = false;

		UI::MouseLbtnUp();

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
		//내 인터페이스랑 인벤토리 둘다 확인
		IconUI* pItem = FindItem(_strName);
		if (pItem != nullptr)
		{
			dynamic_cast<ItemUI*>(pItem)->AddItemNumber(1);
			delete _pItem;
			return;
		}
		IconUI* pInterfaceItem = SceneManger::GetUI<InterfaceUI>()->FindItem(_strName);
		if (pInterfaceItem != nullptr)
		{
			dynamic_cast<ItemUI*>(pInterfaceItem)->AddItemNumber(1);
			delete _pItem;
			return;
		}

		//새로운 아이템
		if (SetItemPosition(_pItem))
		{
			AddChildUI(_pItem, false);
			_pItem->Initialize();
		
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

	bool Inventory::ChangeItemPosition(IconUI* item, Vector2 newPos)
	{
		// 현재 인벤토리 위치와 슬롯 그리드 오프셋 기반으로 가장 가까운 슬롯 계산
		Vector3 invPos = GetComponent<Transform>()->GetPosition();
		Vector2 gridStart(invPos.x + m_vUIStartPosition.x,
			invPos.y + m_vUIStartPosition.y);

		float bestDist = FLT_MAX;
		Vector2 closestSlot;
		UINT targetX = 0, targetY = 0;

		for (UINT y = 0; y < 6; ++y)
		{
			for (UINT x = 0; x < 4; ++x)
			{
				Vector2 slotPos = gridStart + Vector2(x * m_vUIDiffPosition.x,
					y * m_vUIDiffPosition.y);
				float dist = (newPos - slotPos).Length();
				if (dist < bestDist)
				{
					bestDist = dist;
					closestSlot = slotPos;
					targetX = x;
					targetY = y;
				}
			}
		}
		targetY += m_iScrollCurY;

		// 타겟 슬롯에 기존 아이템이 있는지 확인
		IconUI* existing = FindItemOnPosition(targetX, targetY, item);
		int oldX = item->GetItemindexX();
		int oldY = item->GetItemIndexY();
		Vector3 oldWorldPos = item->GetComponent<Transform>()->GetPosition();

		// 다른 UI에서 Inventory로 이동하는 경우 처리
		if (item->GetParentUIType() != eParentUI::Inventory)
		{
			if (existing)
			{
				// 예: Interface UI에서 이동
				if (item->GetParentUIType() == eParentUI::Interface &&
					existing->GetIconType() != IconUI::eIconType::Equip)
				{
					// 기존 아이템 되돌리기
					existing->GetComponent<Transform>()->SetPosition(item->GetStartPosition());
					existing->SetItemIndex(oldX, oldY);
					existing->DeleteParent();
					SceneManger::GetUI<InterfaceUI>()->InsertItem(existing, existing->GetName());
				}
				else if (item->GetParentUIType() == eParentUI::EquipState)
				{
					return false;
				}
			}
			// 새 위치 설정 및 Inventory에 삽입
			item->GetComponent<Transform>()->SetPosition(closestSlot.x, closestSlot.y, oldWorldPos.z);
			item->SetItemIndex(targetX, targetY);
			item->DeleteParent();
			InsertItem(item, item->GetName());
			return true;
		}

		// Inventory 내 이동
		if (existing)
		{
			// 슬롯 교체: 기존 아이템을 원위치
			existing->GetComponent<Transform>()->SetPosition(item->GetStartPosition());
			existing->SetItemIndex(oldX, oldY);
		}

		// 선택 아이템 위치 갱신
		item->GetComponent<Transform>()->SetPosition(closestSlot.x, closestSlot.y, oldWorldPos.z);
		item->SetItemIndex(targetX, targetY);
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
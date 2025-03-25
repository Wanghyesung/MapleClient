#include "WEquipState.h"
#include "WTransform.h"
#include "WInput.h"
#include "WEquip.h"
#include "WSceneManger.h"
#include "WInventory.h"
#include "WPlayer.h"
#include "WHat_10.h"
#include "WWeapon_10.h"
#include "WBottom_10.h"
#include "WTop_10.h"
#include "WShoes_10.h"
#include "WItemManager.h"
namespace W
{
	EquipState::EquipState() :
		m_pPlayer(nullptr),
		m_bRenderOn(false),
		m_bTargetOn(false),
		//m_mapItems{},
		m_vDragStartPos(Vector3::One),
		m_vPandantPosition(Vector2::One),
		m_vHatPosition(Vector2::One),
		m_vTopPosition(Vector2::One),
		m_vBottomPosition(Vector2::One),
		m_vShoesPosition(Vector2::One),
		m_vWeaponPosition(Vector2::One)
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"EquipUITex", L"..\\Resources\\Texture\\UI\\EquipUI\\EquipUI.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		//pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"EquipUIMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	EquipState::~EquipState()
	{
	}
	void EquipState::Initialize()
	{
		//0.634 : 1
		Transform* pTransform = GetComponent<Transform>();
		pTransform->SetPosition(0.f, 0.f, -6.f);
		pTransform->SetScale(0.634f * 3.f, 1.f * 3.f, 0.f); //0.518 : 1

		//m_vUIStartPosition = Vector2();
		//m_vUIEndPosition = Vector2();
		m_vUIDiffPosition = Vector2(0.32f,0.32f);

		//장비 위치 초기화
		m_vPandantPosition = Vector2(0.02f, 0.04f);
		m_vHatPosition = Vector2(-0.32f, 1.05f);;
		m_vTopPosition = Vector2(-0.32f, 0.04f);;
		m_vBottomPosition = Vector2(-0.32f, -0.28f);;
		m_vShoesPosition = Vector2(0.02f, -0.6f);
		m_vWeaponPosition = Vector2(0.34f, 0.04f);


#pragma region Items
		IconUI* pHat = ItemManager::GetClone(L"10_hat");
		pHat->Initialize();
		pHat->GetComponent<Transform>()->SetPosition(Vector3(m_vHatPosition.x, m_vHatPosition.y, 0.f));
		SetEquipPosition(pHat);

		IconUI* pTop10 = ItemManager::GetClone(L"10_top");
		pTop10->Initialize();
		pTop10->GetComponent<Transform>()->SetPosition(Vector3(m_vTopPosition.x, m_vTopPosition.y, 0.f));
		SetEquipPosition(pTop10);
		
		IconUI* pBottom10 = ItemManager::GetClone(L"10_bottom");
		pBottom10->Initialize();
		pBottom10->GetComponent<Transform>()->SetPosition(Vector3(m_vBottomPosition.x, m_vBottomPosition.y, 0.f));
		SetEquipPosition(pBottom10);
		
		IconUI* pShoes10 = ItemManager::GetClone(L"10_shoes");
		pShoes10->Initialize();
		pShoes10->GetComponent<Transform>()->SetPosition(Vector3(m_vShoesPosition.x, m_vShoesPosition.y, 0.f));
		SetEquipPosition(pShoes10);
		
		IconUI* pWeapon10 = ItemManager::GetClone(L"10_weapon");
		pWeapon10->Initialize();
		pWeapon10->GetComponent<Transform>()->SetPosition(Vector3(m_vWeaponPosition.x, m_vWeaponPosition.y, 0.f));
		SetEquipPosition(pWeapon10);


		
#pragma endregion
	}
	void EquipState::Update()
	{
		if (!m_bRenderOn)
			return;

		UI::Update();
	}
	void EquipState::LateUpdate()
	{
		if (!m_bRenderOn)
			return;

		UI::LateUpdate();
	}
	void EquipState::Render()
	{
		if (!m_bRenderOn)
			return;

		UI::Render();
	}
	void EquipState::MouseOn()
	{
		if (m_bTargetOn)
		{
			Transform* pTransform = GetComponent<Transform>();
			Vector2 vMousePos = Input::GetMousePos();

			Vector2 vDiff = vMousePos - m_vDragStartPos;
			Vector3 vPosisition = pTransform->GetPosition() + vDiff;

			pTransform->SetPosition(vPosisition);

			//m_vUIStartPosition += vDiff;
			//m_vUIEndPosition += vDiff;

			MoveToParent(vDiff);

			m_vDragStartPos = Input::GetMousePos();
		}
	}
	void EquipState::MouseLbtnDown()
	{
		m_bTargetOn = true;

		m_vDragStartPos = Input::GetMousePos();
	}
	void EquipState::MouseLbtnUp()
	{
		m_bTargetOn = false;
	}
	void EquipState::MouseLbtnClicked()
	{
	}
	void EquipState::SetEquipPosition(IconUI* _pITem)
	{
		_pITem->DeleteParent();
		_pITem->SetParentUIType(eParentUI::EquipState);

		//이미 장비창에 있는 아이템인지 확인
		Equip* pEquip = dynamic_cast<Equip*>(_pITem);
		Equip::EquipType eType = pEquip->GetEquipType();
		if (eType == Equip::EquipType::None || m_pPlayer == nullptr)
			return;

		check_Equip(pEquip);

		AddChildUI(_pITem,false);
		_pITem->SetItemIndex(-1, -1);

		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		Vector3 vItemPosition = pEquip->GetComponent<Transform>()->GetPosition();

		//이미 아이템이 있다면 인벤토리랑 위치 바꾸기
		switch (eType)
		{
		case W::Equip::EquipType::Pandant:
			pEquip->GetComponent<Transform>()->SetPosition(vPosition.x + m_vPandantPosition.x, vPosition.y + m_vPandantPosition.y,vItemPosition.z);
			break;
		case W::Equip::EquipType::Hat:
			pEquip->GetComponent<Transform>()->SetPosition(vPosition.x + m_vHatPosition.x, vPosition.y + m_vHatPosition.y, vItemPosition.z);
			break;
		case W::Equip::EquipType::Top:
			pEquip->GetComponent<Transform>()->SetPosition(vPosition.x + m_vTopPosition.x, vPosition.y + m_vTopPosition.y, vItemPosition.z);
			break;
		case W::Equip::EquipType::Bottom:
			pEquip->GetComponent<Transform>()->SetPosition(vPosition.x + m_vBottomPosition.x, vPosition.y + m_vBottomPosition.y, vItemPosition.z);
			break;
		case W::Equip::EquipType::Shoes:
			pEquip->GetComponent<Transform>()->SetPosition(vPosition.x + m_vShoesPosition.x, vPosition.y + m_vShoesPosition.y, vItemPosition.z);
			break;
		case W::Equip::EquipType::Weapon:
			pEquip->GetComponent<Transform>()->SetPosition(vPosition.x + m_vWeaponPosition.x, vPosition.y + m_vWeaponPosition.y, vItemPosition.z);
			break;
		}		
		m_pPlayer->SetEquip(pEquip);
	}

	void EquipState::DisableEquip(Equip* _pEquip)
	{
		m_pPlayer->DisableEquip(_pEquip);
	}

	Equip* EquipState::GetEquip(Equip::EquipType _eEquipType)
	{
		std::vector<UI*> m_vecUI = GetChildUI();

		for (UI* pUI : m_vecUI)
		{
			Equip* pEquip = dynamic_cast<Equip*>(pUI);
			if (pEquip == nullptr)
				continue;

			if (pEquip->GetEquipType() == _eEquipType)
				return pEquip;
		}

		return nullptr;
	}

	void EquipState::check_Equip(Equip* _pEquip)
	{
		Equip::EquipType eType = _pEquip->GetEquipType();

		std::vector<UI*> vecUI = GetChildUI();
		
		for (UI* pUI : vecUI)
		{
			Equip* pEquip = dynamic_cast<Equip*>(pUI);
			if (eType == pEquip->GetEquipType())
			{
				Vector3 vStartPos = _pEquip->GetStartPosition();
				SceneManger::GetUI<Inventory>()->ChangeItemPosition(pEquip, Vector2(vStartPos.x, vStartPos.y));
			}
		}
	}
}
#include "WInterfaceUI.h"
#include "WTransform.h"
#include "WInput.h"
#include "WChannleBntUI.h"
#include "WSystemUI.h"
#include "WMenuUI.h"
#include "WStarUI.h"
#include "WShopUI.h"
#include "WGaugeUI.h"
#include "WLevelUI.h"
#include "WInvenUI.h"
#include "WEquipUI.h"
#include "WCharUI.h"
#include "WStatUI.h"
#include "WQuestUI.h"
#include "WSKillUI.h"
#include "WSKill.h"
#include "WInventory.h"
#include "WSKillStorage.h"
#include "WEquipState.h"
#include "WStat.h"
#include "WSceneManger.h"
#include "UIManger.h"
#include "WQuestState.h"
#include "WNumber.h"


namespace W
{
	
	InterfaceUI::InterfaceUI():
		m_mapItems{},
		m_hashKeyCode{},
		m_vUIStartPosition(Vector2::One),
		m_vUIEndPosition(Vector2::One),
		m_vUIDiffPosition(Vector2::One)
	{
		std::shared_ptr<Texture> pInterfaceTex =
			Resources::Load<Texture>(L"InterfaceTex", L"..\\Resources\\Texture\\UI\\Interface\\back_00.png");

		std::shared_ptr<Material> pInterfaceMater = std::make_shared<Material>();
		pInterfaceMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pInterfaceMater->SetTexture(pInterfaceTex);
		Resources::Insert(L"InterfaceMater", pInterfaceMater);
		//pInterfaceMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pUIMeshRenderer = AddComponent<MeshRenderer>();
		pUIMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pUIMeshRenderer->SetMaterial(pInterfaceMater);

#pragma region keyNumber
		//내 인터페이스 키 순서
		std::wstring strNum[20] =
		{
			L"0",L"1",L"2",L"3",L"4",L"5",L"6",L"7",L"8" ,L"9",
			L"q",L"w",L"e",L"r",L"t",L"a", L"s", L"d", L"f", L"g"
		};
		std::wstring strKey[8] = { L"shift",L"ins",L"home",L"pgup",
									L"ctrl",L"del",L"end",L"pdn" };
		float x = 0;
		float y = 0;
		for (UINT i = 0; i < 8; ++i)
		{
			if (i == 4)
			{
				y = -0.34f;
				x = 0.f;
			}
			Number* pNumber = new Number();
			MeshRenderer* pMeshRenderer = pNumber->AddComponent<MeshRenderer>();
			std::wstring strNum = strKey[i];
			std::shared_ptr<Texture> pTex =
				Resources::Load<Texture>(strNum + L"Tex", L"..\\Resources\\Texture\\UI\\InputUI\\" + strNum + L".png");

			std::shared_ptr<Material> Mater = std::make_shared<Material>();
			Mater->SetShader(Resources::Find<Shader>(L"UIShader"));
			Mater->SetTexture(pTex);

			Resources::Insert(strNum + L"Mater", Mater);
			pMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			pMeshRenderer->SetMaterial(Mater);

			pNumber->GetComponent<Transform>()->SetPosition(2.22f + x, -3.1f + y, -8.f);
			pNumber->GetComponent<Transform>()->SetScale(1.8f * 0.1f, 0.9f * 0.1f, 0.f);
			AddChildUI(pNumber);
			x += 0.34f;
		}
		x = 0;
		y = 0;
		for (UINT i = 0; i < 20; ++i)
		{
			if (i == 10)
			{
				y = -0.34f;
				x = 0.f;
			}
			Number* pNumber = new Number();
			MeshRenderer* pMeshRenderer = pNumber->AddComponent<MeshRenderer>();
			std::wstring strNumber = strNum[i];
			std::shared_ptr<Texture> pTex =
				Resources::Load<Texture>(strNumber + L"Tex", L"..\\Resources\\Texture\\UI\\InputUI\\" + strNumber + L".png");

			std::shared_ptr<Material> Mater = std::make_shared<Material>();
			Mater->SetShader(Resources::Find<Shader>(L"UIShader"));
			Mater->SetTexture(pTex);

			Resources::Insert(strNumber + L"Mater", Mater);
			pMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			pMeshRenderer->SetMaterial(Mater);

			pNumber->GetComponent<Transform>()->SetPosition(3.65f + x, -3.1f + y, -8.f);
			pNumber->GetComponent<Transform>()->SetScale(1.f * 0.1f, 1.f * 0.1f, 0.f);
			AddChildUI(pNumber);
			x += 0.34f;
		}
#pragma endregion
	}

	InterfaceUI::~InterfaceUI()
	{
		//AddChildUI()
	}
	void InterfaceUI::Initialize()
	{
		GetComponent<Transform>()->SetPosition(0.f, -3.3f, -2.25f);
		GetComponent<Transform>()->SetScale(16.f * 0.88f, 1.f * 0.88f, 0.f);

		//위치 정보 셋팅
		//2.28 -3.21
		m_vUIStartPosition = Vector2(2.28f, -3.21f);
		//3.3 -3.55
		m_vUIEndPosition = Vector2(6.82f, -3.55f);
		// 0.255 //0.34
		m_vUIDiffPosition = Vector2(0.34f, -0.34f);

		//AlixirUI* pAlixir = new AlixirUI();
		//Transform* pAlixirTransform = pAlixir->GetComponent<Transform>();
		//pAlixirTransform->SetPosition(-0.68f, 1.2f, -0.3f);
		//pAlixirTransform->SetScale(0.1f * 2.5f, 0.1f * 2.5f, 0.f); //0.518 : 1
		//AddItem(pAlixir, pAlixir->GetName());

		//자식UI
#pragma region ChildUI
		//편집으로
		//ChannleBntUI* pChannleUI = new ChannleBntUI();
		//
		//pChannleUI->GetComponent<Transform>()->SetPosition(1.65f,-0.23f,-0.01f);
		//pChannleUI->GetComponent<Transform>()->SetScale(1.5f * 0.5f, 0.7f * 0.5f, 0.f);
		//AddChildUI(pChannleUI);
		//
		//ShopUI* pShopUI = new ShopUI();
		//pShopUI->GetComponent<Transform>()->SetPosition(-0.9f, -0.23f, -0.01f);
		//pShopUI->GetComponent<Transform>()->SetScale(1.1f * 0.5f, 0.7f * 0.5f, 0.f); //11 : 7
		//AddChildUI(pShopUI);
		//
		//StarUI* pStarUI = new StarUI();
		//pStarUI->GetComponent<Transform>()->SetPosition(-0.3f, -0.23f, -0.01f);
		//pStarUI->GetComponent<Transform>()->SetScale(1.1f * 0.5f, 0.7f * 0.5f, 0.f); //11 : 7
		//AddChildUI(pStarUI);
		//
		//MenuUI* pMenuUI = new MenuUI();
		//pMenuUI->GetComponent<Transform>()->SetPosition(0.3f, -0.23f, -0.01f);
		//pMenuUI->GetComponent<Transform>()->SetScale(1.1f * 0.5f, 0.7f * 0.5f, 0.f); //11 : 7
		//AddChildUI(pMenuUI);
		//
		//SystemUI* pSystemUI = new SystemUI();
		//pSystemUI->GetComponent<Transform>()->SetPosition(0.9f, -0.23f, -0.01f);
		//pSystemUI->GetComponent<Transform>()->SetScale(1.1f * 0.5f, 0.7f * 0.5f, 0.f); //11 : 7
		//AddChildUI(pSystemUI);

		//extra
		CharUI* pCharUI = new CharUI();
		pCharUI->GetComponent<Transform>()->SetPosition(-0.77f, 0.06f, -0.01f);
		pCharUI->GetComponent<Transform>()->SetScale(1.619f * 0.17f, 1.f * 0.17f, 0.f); //1.619 : 1
		AddChildUI(pCharUI);

		StatUI* pStatUI = new StatUI();
		pStatUI->GetComponent<Transform>()->SetPosition(-0.45f, 0.06f, -0.01f);
		pStatUI->GetComponent<Transform>()->SetScale(1.619f * 0.17f, 1.f * 0.17f, 0.f); //1.619 : 1
		AddChildUI(pStatUI);

		QuestUI* pQuestUI = new QuestUI();
		pQuestUI->GetComponent<Transform>()->SetPosition(-0.18f, 0.06f, -0.01f);
		pQuestUI->GetComponent<Transform>()->SetScale(1.619f * 0.17f, 1.f * 0.17f, 0.f); //1.619 : 1
		AddChildUI(pQuestUI);

		InvenUI* pInvenUI = new InvenUI();
		pInvenUI->GetComponent<Transform>()->SetPosition(0.14f, 0.06f, -0.01f);
		pInvenUI->GetComponent<Transform>()->SetScale(1.619f * 0.17f, 1.f * 0.17f, 0.f); //1.619 : 1
		AddChildUI(pInvenUI);

		EquipUI* pEquipUI = new EquipUI();
		pEquipUI->GetComponent<Transform>()->SetPosition(0.41f, 0.06f, -0.01f);
		pEquipUI->GetComponent<Transform>()->SetScale(1.619f * 0.17f, 1.f * 0.17f, 0.f); //1.619 : 1
		AddChildUI(pEquipUI);

		SKillUI* pSKillUI = new SKillUI();
		pSKillUI->GetComponent<Transform>()->SetPosition(0.73f, 0.06f, -0.01f);
		pSKillUI->GetComponent<Transform>()->SetScale(1.619f * 0.17f, 1.f * 0.17f, 0.f); //1.619 : 1
		AddChildUI(pSKillUI);

		LevelUI* pLevelUI = new LevelUI();
		pLevelUI->GetComponent<Transform>()->SetPosition(-5.8f, -0.23f, -0.01f);
		pLevelUI->GetComponent<Transform>()->SetScale(6.844 * 0.35f, 1.f * 0.35f, 0.f); //6.844 : 1
		AddChildUI(pLevelUI);

		GaugeUI* pGaugeUI = new GaugeUI();
		pGaugeUI->GetComponent<Transform>()->SetPosition(-2.9f, -0.23f, -0.01f);
		pGaugeUI->GetComponent<Transform>()->SetScale(1.0935 * 3.f, 0.1f * 3.f, 0.f); //10.935 : 1
		AddChildUI(pGaugeUI);
		pGaugeUI->Initialize();
#pragma endregion


#pragma region Extra UI
		Inventory* pInventory = new Inventory();
		SceneManger::AddGameObject(eLayerType::UI, pInventory);
		pInventory->Initialize();

		SKillStorage* pSKillStorage = new SKillStorage();
		SceneManger::AddGameObject(eLayerType::UI, pSKillStorage);
		pSKillStorage->Initialize();

		//EquipState* pEquipState = new EquipState();
		//SceneManger::AddGameObject(eLayerType::UI, pEquipState);
		//pEquipState->Initialize();

		Stat* pStat = new Stat();
		SceneManger::AddGameObject(eLayerType::UI, pStat);
		pStat->Initialize();

		QuestState* pQuest = new QuestState();
		SceneManger::AddGameObject(eLayerType::UI, pQuest);
		pQuest->Initialize();
	

#pragma endregion
	}
	void InterfaceUI::Update()
	{
		UI::Update();
	}
	void InterfaceUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void InterfaceUI::Render()
	{
		UI::Render();
	}
	void InterfaceUI::MouseOn()
	{

	}
	void InterfaceUI::MouseLbtnDown()
	{

	}
	void InterfaceUI::MouseLbtnUp()
	{

	}
	void InterfaceUI::MouseLbtnClicked()
	{

	}

	void InterfaceUI::InsertItem(IconUI* _pItem, std::wstring _strName)
	{
		m_mapItems.insert(std::make_pair(_pItem->GetName(), _pItem));
		AddChildUI(_pItem,false);
		_pItem->SetParentUIType(eParentUI::Interface);

		SetItemKeyCode(_pItem, _pItem->GetItemindexX(), _pItem->GetItemIndexY());
	}

	IconUI* InterfaceUI::FindItem(std::wstring _strName)
	{
		std::map<std::wstring, IconUI*>::iterator iter =
			m_mapItems.find(_strName);

		if(iter == m_mapItems.end())
			return nullptr;

		return iter->second;
	}

	void InterfaceUI::CheckItemPosition(IconUI* _pItem)
	{
		IconUI* pUI = FindItem(_pItem->GetName());

		if (pUI != nullptr)
			return;

		//새로운 아이템
		AddChildUI(_pItem, false);
		m_mapItems.insert(make_pair(_pItem->GetName(), _pItem));

		_pItem->SetParentUIType(eParentUI::Interface);
	}

	
	bool InterfaceUI::ChangeItemPosition(IconUI* _pItem, Vector2 _vSetPosition)
	{
		eKeyCode eItemCode = eKeyCode::END;

		Transform* pTransform = GetComponent<Transform>();
		Vector3 vPosition = pTransform->GetPosition();

		//들어올 아이템 트렌스폼
		Transform* pItemTransform = _pItem->GetComponent<Transform>();
		Vector3 vItemPosition = pItemTransform->GetPosition();

		Vector2 vStartPosition = Vector2(m_vUIStartPosition.x , m_vUIStartPosition.y);
		Vector2 vComaprePos = {};

		//마우스 둔 우치에서 가장 가까운곳 찾기
		Vector2 vMinValue = Vector2(2000.f, 2000.f);
		float fMinLen = 2000.f;
		UINT iMinX = 0;
		UINT iMinY = 0;

		//3.73 3.3 0.34
		for (UINT y = 0; y < 2; ++y)
		{
			vComaprePos.y = vStartPosition.y + y * m_vUIDiffPosition.y;
			for (UINT x = 0; x < 14; ++x)
			{
				vComaprePos.x = vStartPosition.x + x * m_vUIDiffPosition.x;
				
				if (x >= 4)//중간에 끊긴 곳 더하기
					vComaprePos.x += 0.1f;

				Vector2 vDiff = _vSetPosition - vComaprePos;
				float fLen = abs(vDiff.Length());

				//아이템 둔곳에서 가장 가까운곳
				if (fLen <= fMinLen)
				{
					fMinLen = fLen;
					vMinValue = vComaprePos;
					iMinX = x;
					iMinY = y;
				}
			}
		}

		//이미 있는 아이템이 있는 위치인지
		IconUI* pFindItem = FindItemOnPosition(iMinX, iMinY);
		//여기서 구간 나누기 다른 UI에서 왔는지 내 UI에서만 바꾸는건지
		if (_pItem->GetParentUIType() != eParentUI::Interface)
		{
			//찾은 아이템을 들어온 아이템이 있던 UI로 보내기
			if (pFindItem != nullptr)
			{
				eParentUI eParentType = _pItem->GetParentUIType();
				switch (eParentType)
				{
				case W::enums::eParentUI::Inventory:
				{
					if (pFindItem->GetIconType() == IconUI::eIconType::SKill)
						return false;

					Transform* pFindTr = pFindItem->GetComponent<Transform>();
					pFindTr->SetPosition(_pItem->GetStartPosition());
					pFindItem->SetItemIndex(_pItem->GetItemindexX(), _pItem->GetItemIndexY());
					pFindItem->DeleteParent();
					SceneManger::GetUI<Inventory>()->InsertItem(pFindItem, pFindItem->GetName());
				}
					break;

				case W::enums::eParentUI::SkillStorage:
				{
					if(pFindItem->GetIconType() == IconUI::eIconType::Item)
						return false;
					else
					{
						//찾은 아이템 다시 스킬창으로 위치 설정
						SKill* pSKill = dynamic_cast<SKill*>(pFindItem);
						SKill* pSKillClone = pSKill->GetSkillClone();
						if (!pSKillClone)
							return false;
						Vector3 vClonePosition = pSKillClone->GetComponent<Transform>()->GetPosition();
						pFindItem->GetComponent<Transform>()->SetPosition(vClonePosition);

						//자식 UI로 받기
						pFindItem->DeleteParent();
						pFindItem->SetParentUIType(eParentUI::SkillStorage);
						pSKillClone->GetParentUI()->AddChildUI(pFindItem,false);
						pSKill->SetNullClone();
					}
				}
					
				}
			}
			pItemTransform->SetPosition(vMinValue.x, vMinValue.y, vItemPosition.z);
			_pItem->SetItemIndex(iMinX, iMinY);
			_pItem->DeleteParent();
			InsertItem(_pItem, _pItem->GetName());
		}

		//내 UI에서 왔다면
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
				SetItemKeyCode(pFindItem, x, y);
			}
			
			pItemTransform->SetPosition(vMinValue.x, vMinValue.y, vItemPosition.z);
			_pItem->SetItemIndex(iMinX, iMinY);
		}

		SetItemKeyCode(_pItem, iMinX, iMinY);

		return true;
	}





	IconUI* InterfaceUI::FindItemOnPosition(UINT _iX, UINT _iY)
	{
		std::map<std::wstring, IconUI*>::iterator iter = m_mapItems.begin();

		for (iter; iter != m_mapItems.end(); ++iter)
		{
			IconUI* pITem = iter->second;
			UINT ITEM_X = pITem->GetItemindexX();
			UINT ITEM_Y = pITem->GetItemIndexY();

			//빈칸
			if (ITEM_X == _iX && ITEM_Y == _iY)
			{
				return iter->second;
			}
		}
		return nullptr;
	}

	void InterfaceUI::SetItemKeyCode(IconUI* _pItem, UINT _iX, UINT _iY)
	{
		//오른쪽 인터페이스
		UINT iStart = 0;
		
		if (_iX >= 4)
		{
			//오른쪽 인터페이스 시작 위치
			iStart = 4;
			iStart = iStart + _iY * 10 + _iX;
		}
		else
		{
			iStart = _iY * 4 + _iX;
		}

		_pItem->SetKeyCode((eKeyCode)iStart);
	}



}
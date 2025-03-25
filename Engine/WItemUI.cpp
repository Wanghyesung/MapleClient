#include "WItemUI.h"
#include "WSceneManger.h"
#include "WInterfaceUI.h"
#include "WInventory.h"
#include "WInput.h"
#include "WTransform.h"
#include "WNumber.h"
#include "UIManger.h"
#include "WBattleManager.h"
#include "WObject.h"
#include "WPlayerScript.h"
namespace W
{
	ItemUI::ItemUI():
		m_pNumber(nullptr),
		m_iItemCount(0),
		m_fAccHP(0),
		m_fAccMP(0),
		m_iAccCount(1),
		m_vNumberOffset(0.08f,0.07f)
	{
		SetIconType(eIconType::Item);
	}
	ItemUI::ItemUI(const ItemUI& _pItem):
		IconUI(_pItem),
		m_pNumber(nullptr),
		m_iItemCount(0),
		m_fAccHP(_pItem.m_fAccHP),
		m_fAccMP(_pItem.m_fAccMP),
		m_iAccCount(_pItem.m_iAccCount),
		m_pFunction(_pItem.m_pFunction)
	{
		//SetIconType(eIconType::Item);
	}

	ItemUI::~ItemUI()
	{
		int a = 10;
	}

	void ItemUI::Initialize()
	{
		//처음 들어왔을 떄
		m_iItemCount++;
		m_pNumber = new Number();
		MeshRenderer* pMeshRenderer = m_pNumber->AddComponent<MeshRenderer>();

		float z = GetComponent<Transform>()->GetPosition().z;
		m_pNumber->GetComponent<Transform>()->SetPosition(-0.08f, -0.07f, z + -1.1f);
		m_pNumber->GetComponent<Transform>()->SetScale(1.f * 0.08f, 1.f * 0.08f, 0.f);

		SetItemNumber();

		AddChildUI(m_pNumber);
	}
	void ItemUI::Update()
	{
		IconUI::Update();
	}
	void ItemUI::LateUpdate()
	{		
		IconUI::LateUpdate();
	}
	void ItemUI::Render()
	{
		IconUI::Render();
	}
	void ItemUI::MouseOn()
	{
		IconUI::MouseOn();
	}
	void ItemUI::MouseLbtnDown()
	{
		UIManger::SetFoucseUI(GetParentUI());

		IconUI::MouseLbtnDown();
	}
	void ItemUI::MouseLbtnUp()
	{
		Transform* pTransform = GetComponent<Transform>();
		Vector3 vStartPos = GetStartPosition();

		//ResetParentUI();
		//실패하면 원래 있던 자리로
		if (!check_postion())
			pTransform->SetPosition(vStartPos);
	
		//내 아이템 갯수 UI 옮기기
		Vector3 vPosition = pTransform->GetPosition();
		Vector3 vNumberPosition = m_pNumber->GetComponent<Transform>()->GetPosition();

		//인벤토리에 옮겨졌을 때 숫자도 같이 옮겨지게
		Vector3 vDiff = vPosition - vNumberPosition;
		MoveToParent(Vector2(vDiff.x - 0.08f,vDiff.y - 0.07f));

		IconUI::MouseLbtnUp();
	}
	void ItemUI::MouseLbtnClicked()
	{
		IconUI::MouseLbtnClicked();
	}

	ItemUI* ItemUI::Create_Clone()
	{
		return new ItemUI(*this);
	}

	void ItemUI::CheckPosition(int _iDir , Vector2 _vDiff)
	{
		Transform* pTr =GetComponent<Transform>();
		Vector3 vPosition = pTr->GetPosition();
		vPosition.y += (_iDir * _vDiff.y);

		pTr->SetPosition(vPosition);

		Vector3 vNumberPosition = m_pNumber->GetComponent<Transform>()->GetPosition();

		//인벤토리에 옮겨졌을 때 숫자도 같이 옮겨지게
		Vector3 vDiff = vPosition - vNumberPosition;
		MoveToParent(Vector2(vDiff.x - 0.08f, vDiff.y - 0.07f));
	}

	void ItemUI::Using()
	{
		IconUI::eIconType eType = GetIconType();

		bool bActive = false;
		switch (eType)
		{
		case W::IconUI::eIconType::Item:
			bActive = active_item();
			break;
		case W::IconUI::eIconType::Cash:
			bActive = active_cash();
			break;
		}

		if (bActive)
		{
			--m_iItemCount;
			SetItemNumber();
		}

	}

	
	bool ItemUI::check_postion()
	{
		if (check_inventory())
			return true;
		
		else if (check_interface())
			return true;

		return false;
	}
	

	bool ItemUI::check_inventory()
	{
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		Inventory* pInven = SceneManger::GetUI<Inventory>();
		if (!pInven->IsRender())
			return false;
		Transform* pInvenTr = pInven->GetComponent<Transform>();
		Vector3 vInvenPosition = pInvenTr->GetPosition();

		Vector2 vUIStartPosition = pInven->GetStartPosition();
		Vector2 vUIEndPosition = pInven->GetEndPosition();
		Vector2 vUIDiffPosition = pInven->GetDiffPosition();

		Vector2 vEndPosition = Vector2(vInvenPosition + vUIEndPosition);
		Vector2 vStartPosition = Vector2(vInvenPosition + vUIStartPosition);

		//인벤토리 범위 밖이면
		if (!((vPosition.x <= vEndPosition.x + vUIDiffPosition.x && vPosition.x >= vStartPosition.x - vUIDiffPosition.x) &&
			(vPosition.y >= vEndPosition.y + vUIDiffPosition.y && vPosition.y <= vStartPosition.y - vUIDiffPosition.y)))
			return false;
		else
			if (!changepos_inventory())
				return false;

		return true;
	}

	bool ItemUI::changepos_inventory()
	{
		Inventory* pInventroy = SceneManger::GetUI<Inventory>();

		if (pInventroy != nullptr)
		{
			//내 위치
			Vector3 vPosisition = GetComponent<Transform>()->GetPosition();
			Vector2 vComparePosition = Vector2(vPosisition.x, vPosisition.y);

			bool bSuccess = pInventroy->ChangeItemPosition(this, vComparePosition);
			return bSuccess;
		}

		return false;
	}

	bool ItemUI::check_interface()
	{
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		InterfaceUI* pInter = SceneManger::GetUI<InterfaceUI>();
		Transform* pInterTr = pInter->GetComponent<Transform>();

		Vector2 vUIStartPosition = pInter->GetStartPosition();
		Vector2 vUIEndPosition = pInter->GetEndPosition();
		Vector2 vUIDiffPosition = pInter->GetDiffPosition();

		//인벤토리 범위 밖이면
		if (!((vPosition.x <= vUIEndPosition.x + vUIDiffPosition.x && vPosition.x >= vUIStartPosition.x - vUIDiffPosition.x) &&
			(vPosition.y >= vUIEndPosition.y + vUIDiffPosition.y && vPosition.y <= vUIStartPosition.y - vUIDiffPosition.y)))
			return false;
		else
			if (!changepos_interface())
				return false;

		return true;
	}

	bool ItemUI::active_item()
	{
		GameObject* pTarget = SceneManger::FindPlayer();

		if (pTarget == nullptr ||
			pTarget->GetState() != GameObject::eState::Active)
			return false;

		const tObjectInfo& tInfo = SceneManger::FindPlayer()->GetScript<PlayerScript>()->GetObjectInfo();

		if (m_fAccHP > 0.f && tInfo.fHP < tInfo.fMaxHP)
		{
			BattleManager::Buff_Stat(SceneManger::FindPlayer(), BattleManager::eUpStatType::AccHP, m_fAccHP);
			--m_iAccCount;
		}
		if (m_fAccMP > 0.f && tInfo.fMP < tInfo.fMaxMP)
		{
			BattleManager::Buff_Stat(SceneManger::FindPlayer(), BattleManager::eUpStatType::AccMP, m_fAccMP);
			--m_iAccCount;
		}

		if (m_iAccCount < 1)
		{
			m_iAccCount = 1;
			return true;
		}

		return false;
	}

	bool ItemUI::active_cash()
	{
		if (m_pFunction)
		{
			m_pFunction();
			return true;
		}
		return false;
	}

	void ItemUI::SetItemNumber()
	{
		if (m_iItemCount <= 0)
		{
			DeleteParent();
			delete this;
			return;
		}
		MeshRenderer* pMeshRenderer = m_pNumber->GetComponent<MeshRenderer>();

		std::wstring strNum = std::to_wstring(m_iItemCount);
		std::shared_ptr<Material> Mater = Resources::Find<Material>(strNum + L"Mater");
		pMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRenderer->SetMaterial(Mater);
	}

	void ItemUI::AddItemNumber(UINT _iAccNumber)
	{
		m_iItemCount += _iAccNumber;
		MeshRenderer* pMeshRenderer = m_pNumber->GetComponent<MeshRenderer>();

		std::wstring strNum = std::to_wstring(m_iItemCount);
		std::shared_ptr<Material> Mater = Resources::Find<Material>(strNum + L"Mater");
		pMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRenderer->SetMaterial(Mater);
	}

	bool ItemUI::changepos_interface()
	{
		InterfaceUI* pInterface = SceneManger::GetUI<InterfaceUI>();

		if (pInterface != nullptr)
		{
			//내 위치
			Vector3 vPosisition = GetComponent<Transform>()->GetPosition();
			//비교할 내 위치
			Vector2 vComparePosition = Vector2(vPosisition.x, vPosisition.y);

			bool bSuccess = pInterface->ChangeItemPosition(this, vComparePosition);
			return bSuccess;
		}

		return false;
	}

}



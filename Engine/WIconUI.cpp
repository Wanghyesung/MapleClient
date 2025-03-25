#include "WIconUI.h"
#include "WSceneManger.h"
#include "WInterfaceUI.h"
#include "WSKillStorage.h"
#include "WInventory.h"
#include "WInput.h"
#include "WTransform.h"
#include "WEquip.h"
#include "WEquipState.h"
#include "UIManger.h"
#include "WTime.h"
namespace W
{
	IconUI::IconUI():
		m_bTargetOn(false),
		m_vDragStartPos(Vector2::One),
		m_vDragEndPos(Vector2::One),
		m_iItemIndexX(-1),
		m_iItemIndexY(-1),
		m_iPrevIndexX(-1),
		m_iPrevIndexY(-1),
		m_iClickCount(0),
		m_fDoubleClickTime(0.5f),
		m_fCurClickTime(0.f),
		m_eType(eIconType::None),
		m_eParentType(eParentUI::None),
		m_ePrevParentType(eParentUI::None),
		m_eKeyCode(eKeyCode::NONE)
	{
	
	}
	IconUI::IconUI(const IconUI& _pIcon) :
		UI(_pIcon),
		m_bTargetOn(false),
		m_vDragStartPos(Vector2::One),
		m_vDragEndPos(Vector2::One),
		m_iItemIndexX(-1),
		m_iItemIndexY(-1),
		m_iPrevIndexX(-1),
		m_iPrevIndexY(-1),
		m_iClickCount(0),
		m_fDoubleClickTime(0.5f),
		m_fCurClickTime(0.f),
		m_eType(_pIcon.m_eType),
		m_eParentType(eParentUI::None),
		m_ePrevParentType(eParentUI::None),
		m_eKeyCode(eKeyCode::NONE)
	{
	}

	IconUI::~IconUI()
	{
	}
	void IconUI::Initialize()
	{

	}
	void IconUI::Update()
	{
		check_doubleclick();

		if (m_eParentType == eParentUI::Inventory)
		{
			Inventory* pInven = dynamic_cast<Inventory*>(GetParentUI());
			UINT y = pInven->GetScrollCurY();
			if (m_iItemIndexY < y)
				return;

			if (!pInven->IsActivePage((UINT)m_eType))
				return;
		}

		else if (m_eParentType == eParentUI::Interface)
		{
			if(Input::GetKeyDown(m_eKeyCode))
				Using();
		}

		UI::Update();
	}
	void IconUI::LateUpdate()
	{
		if (m_eParentType == eParentUI::Inventory)
		{
			Inventory* pInven = dynamic_cast<Inventory*>(GetParentUI());
			UINT y = pInven->GetScrollCurY();
			if (m_iItemIndexY < y)
				return;

			if (!pInven->IsActivePage((UINT)m_eType))
				return;
		}

		UI::LateUpdate();
	}
	void IconUI::Render()
	{
		if (m_eParentType == eParentUI::Inventory)
		{
			Inventory* pInven = dynamic_cast<Inventory*>(GetParentUI());
			UINT y = pInven->GetScrollCurY();
			if (m_iItemIndexY < y)
				return;

			if (!pInven->IsActivePage((UINT)m_eType))
				return;
		}

		UI::Render();
	}
	void IconUI::MouseOn()
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
	void IconUI::MouseLbtnDown()
	{
		m_bTargetOn = true;

		m_vDragStartPos = Input::GetMousePos();

		Transform* pTransform = GetComponent<Transform>();

		m_vStartPos = pTransform->GetPosition();

		Vector3 vPosition = pTransform->GetPosition();
		vPosition.z = -6.5f;
		pTransform->SetPosition(vPosition);
	}

	void IconUI::MouseLbtnUp()
	{
		m_bTargetOn = false;

		m_vDragEndPos = Input::GetMousePos();
		Transform* pTransform = GetComponent<Transform>();
		Vector3 vPosition = pTransform->GetPosition();

		vPosition.z = m_vStartPos.z;
		pTransform->SetPosition(vPosition);
	}
	void IconUI::MouseLbtnClicked()
	{
		++m_iClickCount;
	}
	void IconUI::DeleteParent()
	{
		switch (m_eParentType)
		{
		case W::enums::eParentUI::Interface:
		{
			UI* pParentUI = GetParentUI();
			InterfaceUI* pInter = dynamic_cast<InterfaceUI*>(pParentUI);
			//interface map
			pInter->DeleteItem(this);
			//vector
			pInter->DeleteChildUI(this);
			m_eKeyCode = eKeyCode::END;
		}
		break;
		case W::enums::eParentUI::Inventory:
		{
			UI* pParentUI = GetParentUI();
			Inventory* pInven = dynamic_cast<Inventory*>(pParentUI);
			pInven->DeleteItem(this);
			pInven->DeleteChildUI(this);
		}
		break;
		case W::enums::eParentUI::SkillStorage:
		{
			UI* pParentUI = GetParentUI();
			pParentUI->DeleteChildUI(this);
		}
		break;
		case W::enums::eParentUI::EquipState:
		{
			UI* pParentUI = GetParentUI();
			Equip* pEquip = dynamic_cast<Equip*>(this);
			dynamic_cast<EquipState*>(pParentUI)->DisableEquip(pEquip);
			pParentUI->DeleteChildUI(this);
		}
		break;
		default:
			break;
		}
	}
	void IconUI::check_doubleclick()
	{
		if (m_iClickCount >= 1)
		{
			m_fCurClickTime += Time::DeltaTime();
			
			if (m_iClickCount >= 2)
			{
				m_fCurClickTime = 0.f;
				m_iClickCount = 0.f;

				Using();
			}

			else if (m_fCurClickTime >= m_fDoubleClickTime)
			{
				m_fCurClickTime = 0.f;
				m_iClickCount = 0.f;
			}

		}
	}

}
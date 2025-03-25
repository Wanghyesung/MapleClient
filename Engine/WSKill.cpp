#include "WSKill.h"
#include "WSKillStorage.h"
#include "WInput.h"
#include "WTransform.h"
#include "WSkillNumber1.h"
#include "WSkillNumber2.h"
#include "WSkillNumber3.h"
#include "WSkillNumber4.h"
#include "WSkillNumber5.h"
#include "WInterfaceUI.h"
#include "WSceneManger.h"
#include "WObject.h"
#include "WPlayer.h"
#include "WSKillNumber6.h"
namespace W
{
	SKill::SKill() :
		m_bTargetOn(false),
		m_bClone(false),
		m_vDragStartPos(Vector2::One),
		m_vStartPos(Vector3::One),
		m_eSkillNuber(SKillStorage::eSkillNuber::None),
		m_pSKillClone(nullptr)
	{
		SetIconType(eIconType::SKill);
		SetParentUIType(eParentUI::SkillStorage);
	}
	SKill::~SKill()
	{

	}
	void SKill::Initialize()
	{

	}
	void SKill::Update()
	{
		IconUI::Update();
	}
	void SKill::LateUpdate()
	{
		IconUI::LateUpdate();
	}
	void SKill::Render()
	{
		IconUI::Render();
	}
	void SKill::MouseOn()
	{
		//스킬을 누르면 해당 스킬에 맞는 UI를 새로 생성
		IconUI::MouseOn();
			
	}
	void SKill::MouseLbtnDown()
	{	
		IconUI::MouseLbtnDown();

		eParentUI eType = GetParentUIType();
		if (eType != eParentUI::SkillStorage)
			return;

		if (m_pSKillClone == nullptr && m_pOwnerClone == nullptr)
			create_clone();
	}
	void SKill::MouseLbtnUp()
	{
		check_interface();

		IconUI::MouseLbtnUp();
	}
	void SKill::MouseLbtnClicked()
	{

	}

	void SKill::Using()
	{
	}

	void SKill::create_clone()
	{
		UI* pParentUI = GetParentUI();
		switch (m_eSkillNuber)
		{
		case W::SKillStorage::eSkillNuber::First:
			m_pSKillClone = dynamic_cast<SkillNumber1*>(pParentUI)->CreateClone(this);//클론만들고 반환받기
			break;
		case W::SKillStorage::eSkillNuber::Second:
			m_pSKillClone = dynamic_cast<SkillNumber2*>(pParentUI)->CreateClone(this);
			break;
		case W::SKillStorage::eSkillNuber::Third:
			m_pSKillClone = dynamic_cast<SkillNumber3*>(pParentUI)->CreateClone(this);
			break;
		case W::SKillStorage::eSkillNuber::Four:
			m_pSKillClone = dynamic_cast<SkillNumber4*>(pParentUI)->CreateClone(this);
			break;
		case W::SKillStorage::eSkillNuber::Five:
			m_pSKillClone = dynamic_cast<SkillNumber5*>(pParentUI)->CreateClone(this);
			break;
		case W::SKillStorage::eSkillNuber::Six:
			m_pSKillClone = dynamic_cast<SkillNumber6*>(pParentUI)->CreateClone(this);
			break;
		}
	}

	void SKill::check_interface()
	{
		InterfaceUI* pInterface = SceneManger::GetUI<InterfaceUI>();

		Vector2 vUIStartPosition = pInterface->GetStartPosition();
		Vector2 vUIEndPosition = pInterface->GetEndPosition();
		Vector2 vUIDiffPosition = pInterface->GetDiffPosition();
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		if (!((vPosition.x <= vUIEndPosition.x + vUIDiffPosition.x && vPosition.x >= vUIStartPosition.x - vUIDiffPosition.x) &&
			(vPosition.y >= vUIEndPosition.y + vUIDiffPosition.y && vPosition.y <= vUIStartPosition.y - vUIDiffPosition.y)))
		{

			if (GetParentUIType() == eParentUI::SkillStorage)
			{
				object::Destroy(m_pSKillClone);
				Vector3 vStartPos = GetStartPosition();
				GetComponent<Transform>()->SetPosition((vStartPos));
			}
			else
			{
				vPosition = m_pSKillClone->GetComponent<Transform>()->GetPosition();
				GetComponent<Transform>()->SetPosition(vPosition);

				pInterface->DeleteChildUI(this);
				pInterface->DeleteItem(this);

				m_pSKillClone->GetParentUI()->AddChildUI(this, false);
				SetParentUIType(eParentUI::SkillStorage);

				object::Destroy(m_pSKillClone);
			}
		}
			
		else
		{
			if (!changepos_interface())//실패하면
			{
				object::Destroy(m_pSKillClone);
				Vector3 vStartPos = GetStartPosition();
				GetComponent<Transform>()->SetPosition((vStartPos));
			}
		}
		
		m_pSKillClone = nullptr;
	}

	bool SKill::changepos_interface()
	{
		Vector3 vSKillPosition = GetComponent<Transform>()->GetPosition();
		bool bSuccess = SceneManger::GetUI<InterfaceUI>()->ChangeItemPosition(this, Vector2(vSKillPosition.x, vSKillPosition.y));

		return bSuccess;
	}

}
#include "WSkillNumber5.h"
#include "WSKillStorage.h"
#include "WSKillBox.h"
#include "WSkillBlastUI.h"
#include "WSkillLoadUI.h"
#include "WSkillWindUI.h"
#include "WSkillUltimateUI.h"
namespace W
{
	SkillNumber5::SkillNumber5() :
		SkillNumber(SKillStorage::eSkillNuber::Five)

	{

	}
	SkillNumber5::~SkillNumber5()
	{

	}
	void SkillNumber5::Initialize()
	{
		SKillBox* pSKillBox1 = new SKillBox();
		pSKillBox1->SetName(L"SKillBox1");
		Transform* pBoxTransform1 = pSKillBox1->GetComponent<Transform>();
		pBoxTransform1->SetPosition(-0.75f, -0.8f, -0.01f);
		pBoxTransform1->SetScale(0.4f * 3.5f, 0.1f * 3.5f, 0.f); //4 : 1
		AddChildUI(pSKillBox1);

		m_vQSSkillPosition = Vector3(-1.255f, -0.8f, -0.03f);
		SkillBlastUI* pSkill1 = new SkillBlastUI();
		pSkill1->SetName(L"QSSkill");
		pSkill1->SetSkillNuber(SKillStorage::eSkillNuber::Five);
		Transform* pTransform = pSkill1->GetComponent<Transform>();
		pTransform->SetPosition(m_vQSSkillPosition);
		pTransform->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
		AddChildUI(pSkill1);

		//내 스킬 박스
		SKillBox* pSKillBox2 = new SKillBox();
		pSKillBox2->SetName(L"SKillBox2");
		Transform* pBoxTransform2 = pSKillBox2->GetComponent<Transform>();
		pBoxTransform2->SetPosition(0.85f, -0.8f, -0.01f);
		pBoxTransform2->SetScale(0.4f * 3.5f, 0.1f * 3.5f, 0.f); //4 : 1
		AddChildUI(pSKillBox2);

		m_vRadeSkillPosition = Vector3(0.33f, -0.8f, -0.03f);
		SkillLoadUI* pSKill2 = new SkillLoadUI();
		pSKill2->SetName(L"RadeSKill");
		pSKill2->SetSkillNuber(SKillStorage::eSkillNuber::Five);
		Transform* pTransform2 = pSKill2->GetComponent<Transform>();
		pTransform2->SetPosition(m_vRadeSkillPosition);
		pTransform2->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
		AddChildUI(pSKill2);

		SKillBox* pSKillBox3 = new SKillBox();
		pSKillBox3->SetName(L"SKillBox3");
		Transform* pBoxTransform3 = pSKillBox3->GetComponent<Transform>();
		pBoxTransform3->SetPosition(-0.75f, -1.3f, -0.01f);
		pBoxTransform3->SetScale(0.4f * 3.5f, 0.1f * 3.5f, 0.f); //4 : 1
		AddChildUI(pSKillBox3);

		m_vWindSkillPosition = Vector3(-1.255f, -1.3f, -0.03f);
		SkillWindUI* pSkill3 = new SkillWindUI();
		pSkill3->SetName(L"WindSkill");
		pSkill3->SetSkillNuber(SKillStorage::eSkillNuber::Five);
		Transform* pTransform3 = pSkill3->GetComponent<Transform>();
		pTransform3->SetPosition(m_vWindSkillPosition);
		pTransform3->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
		AddChildUI(pSkill3);


		
	}

	void SkillNumber5::Update()
	{
		SkillNumber::Update();
	}
	void SkillNumber5::LateUpdate()
	{
		SkillNumber::LateUpdate();
	}
	void SkillNumber5::Render()
	{
		SkillNumber::Render();
	}
	void SkillNumber5::MouseOn()
	{

	}
	void SkillNumber5::MouseLbtnDown()
	{
		SkillNumber::MouseLbtnDown();
	}
	void SkillNumber5::MouseLbtnUp()
	{

	}
	void SkillNumber5::MouseLbtnClicked()
	{

	}

	SKill* SkillNumber5::CreateClone(SKill* _pSkill)
	{
		if (dynamic_cast<SkillBlastUI*>(_pSkill))
		{
			SkillBlastUI* pSkill1 = new SkillBlastUI();
			pSkill1->SetName(L"DarkSkill");
			pSkill1->SetSkillNuber(SKillStorage::eSkillNuber::Five);
			pSkill1->SetClone(true);
			pSkill1->SetOwner(_pSkill);
			Transform* pDarkTr = pSkill1->GetComponent<Transform>();
			pDarkTr->SetPosition(m_vQSSkillPosition);
			pDarkTr->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
			AddChildUI(pSkill1);
			return pSkill1;
		}
		else if (dynamic_cast<SkillLoadUI*>(_pSkill))
		{
			SkillLoadUI* pSkill2 = new SkillLoadUI();
			pSkill2->SetName(L"DarkSkill");
			pSkill2->SetSkillNuber(SKillStorage::eSkillNuber::Five);
			pSkill2->SetClone(true);
			pSkill2->SetOwner(_pSkill);
			Transform* pLuckTr = pSkill2->GetComponent<Transform>();
			pLuckTr->SetPosition(m_vRadeSkillPosition);
			pLuckTr->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
			AddChildUI(pSkill2);
			return pSkill2;
		}

		else if (dynamic_cast<SkillWindUI*>(_pSkill))
		{
			SkillWindUI* pSkill3 = new SkillWindUI();
			pSkill3->SetName(L"DarkSkill");
			pSkill3->SetSkillNuber(SKillStorage::eSkillNuber::Five);
			pSkill3->SetClone(true);
			pSkill3->SetOwner(_pSkill);
			Transform* pLuckTr = pSkill3->GetComponent<Transform>();
			pLuckTr->SetPosition(m_vWindSkillPosition);
			pLuckTr->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
			AddChildUI(pSkill3);
			return pSkill3;
		}


		return nullptr;
	}
}
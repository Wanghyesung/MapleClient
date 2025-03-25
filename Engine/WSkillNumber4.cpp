#include "WSkillNumber4.h"
#include "WSKillStorage.h"
#include "WSKillBox.h"
#include "WSkillRaidUI.h"
#include "WSKillQSUI.h"
namespace W
{
	SkillNumber4::SkillNumber4() :
		SkillNumber(SKillStorage::eSkillNuber::Four)

	{

	}
	SkillNumber4::~SkillNumber4()
	{
	}
	void SkillNumber4::Initialize()
	{
		SKillBox* pSKillBox1 = new SKillBox();
		pSKillBox1->SetName(L"SKillBox1");
		Transform* pBoxTransform1 = pSKillBox1->GetComponent<Transform>();
		pBoxTransform1->SetPosition(-0.5f, -0.8f, -0.01f);
		pBoxTransform1->SetScale(0.4f * 3.5f, 0.1f * 3.5f, 0.f); //4 : 1
		AddChildUI(pSKillBox1);

		m_vQSSkillPosition = Vector3(-1.005f, -0.8f, -0.02f);
		SkillQSUI* pSkill1 = new SkillQSUI();
		pSkill1->SetName(L"QSSkill");
		pSkill1->SetSkillNuber(SKillStorage::eSkillNuber::Four);
		Transform* pTransform = pSkill1->GetComponent<Transform>();
		pTransform->SetPosition(m_vQSSkillPosition);
		pTransform->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
		AddChildUI(pSkill1);

		//내 스킬 박스
		SKillBox* pSKillBox2 = new SKillBox();
		pSKillBox2->SetName(L"SKillBox2");
		Transform* pBoxTransform2 = pSKillBox2->GetComponent<Transform>();
		pBoxTransform2->SetPosition(1.05f, -0.8f, -0.01f);
		pBoxTransform2->SetScale(0.4f * 3.5f, 0.1f * 3.5f, 0.f); //4 : 1
		AddChildUI(pSKillBox2);

		m_vRadeSkillPosition = Vector3(0.53f, -0.8f, -0.02f);
		SkillRaidUI* pSKill2 = new SkillRaidUI();
		pSKill2->SetName(L"RadeSKill");
		pSKill2->SetSkillNuber(SKillStorage::eSkillNuber::Four);
		Transform* pTransform2 = pSKill2->GetComponent<Transform>();
		pTransform2->SetPosition(m_vRadeSkillPosition);
		pTransform2->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
		AddChildUI(pSKill2);
	}

	void SkillNumber4::Update()
	{
		SkillNumber::Update();
	}
	void SkillNumber4::LateUpdate()
	{
		SkillNumber::LateUpdate();
	}
	void SkillNumber4::Render()
	{
		SkillNumber::Render();
	}
	void SkillNumber4::MouseOn()
	{

	}
	void SkillNumber4::MouseLbtnDown()
	{
		SkillNumber::MouseLbtnDown();
	}
	void SkillNumber4::MouseLbtnUp()
	{

	}
	void SkillNumber4::MouseLbtnClicked()
	{

	}

	SKill* SkillNumber4::CreateClone(SKill* _pSkill)
	{
		if (dynamic_cast<SkillQSUI*>(_pSkill))
		{
			SkillQSUI* pSkill1 = new SkillQSUI();
			pSkill1->SetName(L"DarkSkill");
			pSkill1->SetSkillNuber(SKillStorage::eSkillNuber::Four);
			pSkill1->SetClone(true);
			pSkill1->SetOwner(_pSkill);
			Transform* pDarkTr = pSkill1->GetComponent<Transform>();
			pDarkTr->SetPosition(m_vQSSkillPosition);
			pDarkTr->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
			AddChildUI(pSkill1);
			return pSkill1;
		}
		else if (dynamic_cast<SkillRaidUI*>(_pSkill))
		{
			SkillRaidUI* pSkill2 = new SkillRaidUI();
			pSkill2->SetName(L"DarkSkill");
			pSkill2->SetSkillNuber(SKillStorage::eSkillNuber::Four);
			pSkill2->SetClone(true);
			pSkill2->SetOwner(_pSkill);
			Transform* pLuckTr = pSkill2->GetComponent<Transform>();
			pLuckTr->SetPosition(m_vRadeSkillPosition);
			pLuckTr->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
			AddChildUI(pSkill2);
			return pSkill2;
		}

		return nullptr;
	}
}
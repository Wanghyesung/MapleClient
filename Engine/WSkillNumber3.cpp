#include "WSkillNumber3.h"
#include "WSKillStorage.h"
#include "WSKillBox.h"
#include "WSkillAvenUI.h"
#include "WSkillShadowUI.h"
namespace W
{
	SkillNumber3::SkillNumber3():
		SkillNumber(SKillStorage::eSkillNuber::Third)

	{

	}
	SkillNumber3::~SkillNumber3()
	{
	}
	void SkillNumber3::Initialize()
	{
		SKillBox* pSKillBox1 = new SKillBox();
		pSKillBox1->SetName(L"SKillBox1");
		Transform* pBoxTransform1 = pSKillBox1->GetComponent<Transform>();
		pBoxTransform1->SetPosition(-0.25f, -0.8f, -0.01f);
		pBoxTransform1->SetScale(0.4f * 3.5f, 0.1f * 3.5f, 0.f); //4 : 1
		AddChildUI(pSKillBox1);

		m_vAvenSkillPosition = Vector3(-0.755f, -0.8f, -0.02f);
		SkillAvenUI* pSkill1 = new SkillAvenUI();
		pSkill1->SetName(L"AvenSkill");
		pSkill1->SetSkillNuber(SKillStorage::eSkillNuber::Third);
		Transform* pTransform = pSkill1->GetComponent<Transform>();
		pTransform->SetPosition(m_vAvenSkillPosition);
		pTransform->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
		AddChildUI(pSkill1);

		//내 스킬 박스
		SKillBox* pSKillBox2 = new SKillBox();
		pSKillBox2->SetName(L"SKillBox2");
		Transform* pBoxTransform2 = pSKillBox2->GetComponent<Transform>();
		pBoxTransform2->SetPosition(1.3f, -0.8f, -0.01f);
		pBoxTransform2->SetScale(0.4f * 3.5f, 0.1f * 3.5f, 0.f); //4 : 1
		AddChildUI(pSKillBox2);

		m_vShadowSkillPosition = Vector3(0.78f, -0.8f, -0.02f);
		SkillShadowUI* pSKill2 = new SkillShadowUI();
		pSKill2->SetName(L"ShadowSKill");
		pSKill2->SetSkillNuber(SKillStorage::eSkillNuber::Third);
		Transform* pTransform2 = pSKill2->GetComponent<Transform>();
		pTransform2->SetPosition(m_vShadowSkillPosition);
		pTransform2->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
		AddChildUI(pSKill2);
	}

	void SkillNumber3::Update()
	{
		SkillNumber::Update();
	}
	void SkillNumber3::LateUpdate()
	{
		SkillNumber::LateUpdate();
	}
	void SkillNumber3::Render()
	{
		SkillNumber::Render();
	}
	void SkillNumber3::MouseOn()
	{

	}
	void SkillNumber3::MouseLbtnDown()
	{
		SkillNumber::MouseLbtnDown();
	}
	void SkillNumber3::MouseLbtnUp()
	{

	}
	void SkillNumber3::MouseLbtnClicked()
	{

	}

	SKill* SkillNumber3::CreateClone(SKill* _pSkill)
	{
		if (dynamic_cast<SkillAvenUI*>(_pSkill))
		{
			SkillAvenUI* pSkill1 = new SkillAvenUI();
			pSkill1->SetName(L"DarkSkill");
			pSkill1->SetSkillNuber(SKillStorage::eSkillNuber::Third);
			pSkill1->SetClone(true);
			pSkill1->SetOwner(_pSkill);
			Transform* pDarkTr = pSkill1->GetComponent<Transform>();
			pDarkTr->SetPosition(m_vAvenSkillPosition);
			pDarkTr->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
			AddChildUI(pSkill1);
			return pSkill1;
		}
		else if (dynamic_cast<SkillShadowUI*>(_pSkill))
		{
			SkillShadowUI* pSkill2 = new SkillShadowUI();
			pSkill2->SetName(L"DarkSkill");
			pSkill2->SetSkillNuber(SKillStorage::eSkillNuber::Third);
			pSkill2->SetClone(true);
			pSkill2->SetOwner(_pSkill);
			Transform* pLuckTr = pSkill2->GetComponent<Transform>();
			pLuckTr->SetPosition(m_vShadowSkillPosition);
			pLuckTr->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
			AddChildUI(pSkill2);
			return pSkill2;
		}

		return nullptr;
	}
}
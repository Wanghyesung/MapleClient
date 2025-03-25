#include "WSkillNumber6.h"
#include "WSKillBox.h"
#include "WSKill.h"
#include "WSKillStorage.h"
#include "WSkillUltimateUI.h"

namespace W
{
	SkillNumber6::SkillNumber6() :
		SkillNumber(SKillStorage::eSkillNuber::Six)
	{


	}
	SkillNumber6::~SkillNumber6()
	{

	}
	void SkillNumber6::Initialize()
	{
		//내 스킬 박스
		SKillBox* pSKillBox1 = new SKillBox();
		pSKillBox1->SetName(L"SKillBox1");
		Transform* pBoxTransform1 = pSKillBox1->GetComponent<Transform>();
		pBoxTransform1->SetPosition(-1.f, -0.8f, -0.01f);
		pBoxTransform1->SetScale(0.4f * 3.5f, 0.1f * 3.5f, 0.f); //4 : 1
		AddChildUI(pSKillBox1);


		m_vUltimateSkillPosition = Vector3(-1.505f, -0.8f, -0.02f);
		SkillUltimateUI* pSkill4 = new SkillUltimateUI();
		pSkill4->SetName(L"UltimateSkill");
		pSkill4->SetSkillNuber(SKillStorage::eSkillNuber::Six);
		Transform* pTransform4 = pSkill4->GetComponent<Transform>();
		pTransform4->SetPosition(m_vUltimateSkillPosition);
		pTransform4->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
		AddChildUI(pSkill4);
	}
	void SkillNumber6::Update()
	{
		SkillNumber::Update();
	}
	void SkillNumber6::LateUpdate()
	{
		SkillNumber::LateUpdate();
	}
	void SkillNumber6::Render()
	{
		SkillNumber::Render();
	}
	void SkillNumber6::MouseOn()
	{

	}
	void SkillNumber6::MouseLbtnDown()
	{
		SkillNumber::MouseLbtnDown();
	}
	void SkillNumber6::MouseLbtnUp()
	{


	}
	void SkillNumber6::MouseLbtnClicked()
	{

	}

	SKill* SkillNumber6::CreateClone(SKill* _pSkill)
	{
		if (dynamic_cast<SkillUltimateUI*>(_pSkill))
		{
			SkillUltimateUI* pSkill = new SkillUltimateUI();
			pSkill->SetName(L"UltimateSkill");
			pSkill->SetSkillNuber(SKillStorage::eSkillNuber::Six);
			pSkill->SetClone(true);
			pSkill->SetOwner(_pSkill);
			Transform* pLuckTr = pSkill->GetComponent<Transform>();
			pLuckTr->SetPosition(m_vUltimateSkillPosition);
			pLuckTr->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
			AddChildUI(pSkill);
			return pSkill;
		}

	}

}
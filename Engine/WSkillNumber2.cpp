#include "WSkillNumber2.h"
#include "WSKillStorage.h"
#include "WSKillBox.h"
#include "WSKillSpeedUI.h"
#include "WSKillJumpUI.h"

//비율좌표이기 떄문에 최대가 1
//shader에 넘길 수 있게

namespace W
{
	SkillNumber2::SkillNumber2():
		SkillNumber(SKillStorage::eSkillNuber::Second),
		m_vJumpSkillPosition(Vector3::One),
		m_vSpeedSkillPosition(Vector3::One)
	{
		
	}
	SkillNumber2::~SkillNumber2()
	{

	}
	void SkillNumber2::Initialize()
	{
		SKillBox* pSKillBox1 = new SKillBox();
		pSKillBox1->SetName(L"SKillBox1");
		Transform* pBoxTransform1 = pSKillBox1->GetComponent<Transform>();
		pBoxTransform1->SetPosition(0.f, -0.8f, -0.01f);
		pBoxTransform1->SetScale(0.4f * 3.5f, 0.1f * 3.5f, 0.f); //4 : 1
		AddChildUI(pSKillBox1);

		m_vJumpSkillPosition = Vector3(-0.505f, -0.8f, -0.02f);
		SKillJumpUI* pSkill1 = new SKillJumpUI();
		pSkill1->SetName(L"DarkSkill");
		pSkill1->SetSkillNuber(SKillStorage::eSkillNuber::Second);
		Transform* pDarkTr = pSkill1->GetComponent<Transform>();
		pDarkTr->SetPosition(m_vJumpSkillPosition);pDarkTr->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
		AddChildUI(pSkill1);

		//내 스킬 박스
		SKillBox* pSKillBox2 = new SKillBox();
		pSKillBox2->SetName(L"SKillBox2");
		Transform* pBoxTransform2 = pSKillBox2->GetComponent<Transform>();
		pBoxTransform2->SetPosition(1.55f, -0.8f, -0.01f);
		pBoxTransform2->SetScale(0.4f * 3.5f, 0.1f * 3.5f, 0.f); //4 : 1
		AddChildUI(pSKillBox2);

		m_vSpeedSkillPosition = Vector3(1.03f, -0.8f, -0.02f);
		SkillSpeedUI* pSKill2 = new SkillSpeedUI();
		pSKill2->SetName(L"LuckSkill");
		pSKill2->SetSkillNuber(SKillStorage::eSkillNuber::Second);
		Transform* pLuckTr = pSKill2->GetComponent<Transform>();
		pLuckTr->SetPosition(m_vSpeedSkillPosition);
		pLuckTr->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
		AddChildUI(pSKill2);
	}

	void SkillNumber2::Update()
	{
		SkillNumber::Update();
	}
	void SkillNumber2::LateUpdate()
	{
		SkillNumber::LateUpdate();
	}
	void SkillNumber2::Render()
	{
		SkillNumber::Render();
	}
	void SkillNumber2::MouseOn()
	{
	
	}
	void SkillNumber2::MouseLbtnDown()
	{
		SkillNumber::MouseLbtnDown();
	}
	void SkillNumber2::MouseLbtnUp()
	{

	}
	void SkillNumber2::MouseLbtnClicked()
	{

	}
	
	SKill* SkillNumber2::CreateClone(SKill* _pSkill)
	{
		if (dynamic_cast<SkillSpeedUI*>(_pSkill))
		{
			SkillSpeedUI* pSkill1 = new SkillSpeedUI();
			pSkill1->SetName(L"DarkSkill");
			pSkill1->SetSkillNuber(SKillStorage::eSkillNuber::Second);
			pSkill1->SetClone(true);
			pSkill1->SetOwner(_pSkill);
			Transform* pDarkTr = pSkill1->GetComponent<Transform>();
			pDarkTr->SetPosition(m_vSpeedSkillPosition);
			pDarkTr->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
			AddChildUI(pSkill1);
			return pSkill1;
		}
		else if (dynamic_cast<SKillJumpUI*>(_pSkill))
		{
			SKillJumpUI* pJumpSkill = new SKillJumpUI();
			pJumpSkill->SetName(L"DarkSkill");
			pJumpSkill->SetSkillNuber(SKillStorage::eSkillNuber::Second);
			pJumpSkill->SetClone(true);
			pJumpSkill->SetOwner(_pSkill);
			Transform* pLuckTr = pJumpSkill->GetComponent<Transform>();
			pLuckTr->SetPosition(m_vJumpSkillPosition);
			pLuckTr->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
			AddChildUI(pJumpSkill);
			return pJumpSkill;
		}

		return nullptr;
	}
}
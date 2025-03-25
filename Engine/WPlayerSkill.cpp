#include "WPlayerSkill.h"
#include "WSkillManager.h"
#include "WSkillState.h"



namespace W
{
	PlayerSkill::PlayerSkill():
		m_pActiveSkill(nullptr),
		m_bSkillOn(false)
	{
	}

	PlayerSkill::~PlayerSkill()
	{
		SkillManager::Release();
	}

	void PlayerSkill::Update()
	{
		if (m_pActiveSkill)
			m_pActiveSkill->Update();
	}

	void PlayerSkill::Initialize()
	{
		SkillManager::SetPlayerSkill(this);
		SkillManager::Initialize();
	}

}
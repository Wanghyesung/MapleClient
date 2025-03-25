#include "WSkillManager.h"
#include "WSkillLuck.h"
#include "WSkillDark.h"
#include "WSkillJump.h"
#include "WSkillSpeed.h"
#include "WSkillAven.h"
#include "WSkillShadow.h"
#include "WSkillQuad.h"
#include "WSkillRaid.h"
#include "WSkillWind.h"
#include "WSkillBlast.h"
#include "WSkillLoad.h"
#include "WPlayerScript.h"
#include "WUltimateSkill.h"
#include "WTime.h"
namespace W
{
	std::map<Player::ePlayerSkill, SkillState*> SkillManager::m_mapSkills = {};
	std::map<Player::ePlayerSkill, tSkillTime> SkillManager::m_mapSkillTime = {};
	PlayerSkill* SkillManager::m_pPlayerSkill = nullptr;

	//플레이어꺼 쓰기
	void SkillManager::Update()
	{
		update_skill();
	}
	void SkillManager::Initialize()
	{
		AddSkill(new SkillLuck());
		AddSkill(new SkillDark());
		AddSkill(new SkillJump());
		AddSkill(new SkillSpeed());
		AddSkill(new SkillAven());
		AddSkill(new SkillShadow());
		AddSkill(new SkillQuad());
		AddSkill(new SkillRaid());
		AddSkill(new SkillWind());
		AddSkill(new SkillBlast());
		AddSkill(new SkillLoad());
		AddSkill(new SkillUltimate());
	}

	void SkillManager::AddSkill(SkillState* _pSkill)
	{
		Player::ePlayerSkill eSkill = _pSkill->GetPlayerSkill();

		SkillState* pSkill = FindSkillState(eSkill);
		//똑같은 스킬

		if (pSkill)
			assert(nullptr);

		_pSkill->SetOnwer(m_pPlayerSkill);
		_pSkill->Initialize();
		m_mapSkills.insert(std::make_pair(eSkill, _pSkill));
		m_mapSkillTime.insert(std::make_pair(eSkill, _pSkill->GetCoolTime()));
	}

	void SkillManager::SetActiveSkill(Player::ePlayerSkill _eSkill)
	{
		PlayerScript* pScript = m_pPlayerSkill->m_pPlayer->GetScript<PlayerScript>();
	
		if (_eSkill == Player::ePlayerSkill::end)
		{
			m_pPlayerSkill->m_pActiveSkill = nullptr;
			m_pPlayerSkill->m_bSkillOn = false;
			return;
		}

		if (m_pPlayerSkill->m_pActiveSkill != nullptr)
			return;

		if (!check_cooltime(_eSkill))
			return;

		if (pScript->IsAbnormal() || pScript->IsAttack() || pScript->IsSealSkill())
			return;

		m_pPlayerSkill->m_pActiveSkill = FindSkillState(_eSkill);

		m_pPlayerSkill->m_bSkillOn = true;
		m_pPlayerSkill->m_pActiveSkill->Enter();
		set_max(_eSkill);
	}

	SkillState* SkillManager::FindSkillState(Player::ePlayerSkill _eSkill)
	{
		std::map<Player::ePlayerSkill, SkillState*>::iterator iter =
			m_mapSkills.find(_eSkill);

		if (iter != m_mapSkills.end())
			return iter->second;

		return nullptr;
	}
	void SkillManager::AccAttack(math::Vector3 _vPosition)
	{
		PlayerScript* pScript = m_pPlayerSkill->m_pPlayer->GetScript<PlayerScript>();
		
		SkillState* pState = FindSkillState(Player::ePlayerSkill::blast);
		SkillBlast* pBlast = dynamic_cast<SkillBlast*>(pState);
		_vPosition.z -= 1.f;
		pBlast->create_blast(_vPosition);
		pScript->MinusAttackCnt();
	
	}
	void SkillManager::Release()
	{
		std::map<Player::ePlayerSkill, SkillState*>::iterator iter =
			m_mapSkills.begin();

		for (iter; iter != m_mapSkills.end(); ++iter)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
	void SkillManager::update_skill()
	{
		std::map<Player::ePlayerSkill, tSkillTime>::iterator iter =
			m_mapSkillTime.begin();

		for (iter; iter != m_mapSkillTime.end(); ++iter)
		{
			tSkillTime& tTime = iter->second;
			if (tTime.fCurTime > 0.f)
			{
				tTime.fCurTime -= Time::DeltaTime();
			}
		}
	}
	void SkillManager::set_max(Player::ePlayerSkill _eTarget)
	{
		std::map<Player::ePlayerSkill, tSkillTime>::iterator iter =
			m_mapSkillTime.find(_eTarget);

		tSkillTime& tTime = iter->second;
		tTime.fCurTime = tTime.fCoolTime;
	}

	bool SkillManager::check_cooltime(Player::ePlayerSkill _eTarget)
	{
		std::map<Player::ePlayerSkill, tSkillTime>::iterator iter =
			m_mapSkillTime.find(_eTarget);

		tSkillTime tTime = iter->second;
		if (tTime.fCurTime <= 0.f)
			return true;

		return false;
	}
}
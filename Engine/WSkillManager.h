#pragma once
#include "WPlayer.h"
#include "WInfo.h"
#include "WSkillState.h"

namespace W
{
	class PlayerSkill;

	class SkillManager
	{
	public:
		static void Update();
		static void Initialize();
		static void Release();

		static void AddSkill(SkillState* _pSkill);
		static void SetPlayerSkill(PlayerSkill* _pSkill){ m_pPlayerSkill = _pSkill;}
		static void SetActiveSkill(Player::ePlayerSkill _eSkill);
		static SkillState* FindSkillState(Player::ePlayerSkill _eSkill);

		static void AccAttack(math::Vector3 _vPosition);

	private:
		static void update_skill();
		static void set_max(Player::ePlayerSkill _eTarget);
		static bool check_cooltime(Player::ePlayerSkill _eTarget);

	private:
		static PlayerSkill* m_pPlayerSkill;

		static std::map<Player::ePlayerSkill, SkillState*> m_mapSkills;
		static std::map<Player::ePlayerSkill, tSkillTime> m_mapSkillTime;
	};
}



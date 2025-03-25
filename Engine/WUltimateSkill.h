#pragma once
#include "WSkillState.h"
namespace W
{
	class UltimateObject;

	class SkillUltimate : public SkillState
	{
	public:
		SkillUltimate();
		virtual ~SkillUltimate();

		virtual void Update()override;
		virtual void Initialize()override;

		virtual void Enter()override;
		virtual void Exit()override;

	private:
		void activeskill_ultimate();
		void create_shuriken();

	private:
		bool m_bCreate;
		UltimateObject* m_pUltimateSkill;

	};

}


#pragma once
#include "WSkillState.h"

namespace W
{
	class SkillRaid : public SkillState
	{
	public:
		SkillRaid();
		virtual ~SkillRaid();

		virtual void Update()override;
		virtual void Initialize()override;

		virtual void Enter()override;
		virtual void Exit()override;

	private:
		void create_raid();
		void activeskill_raid();

		void fade_out();

	private:
		bool m_bCreate;

		class Effect* m_pFadeEffect;
	};
}




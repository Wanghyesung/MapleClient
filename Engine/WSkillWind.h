#pragma once
#include "WSkillState.h"

namespace W
{
	class SkillWind : public SkillState
	{
	public:
		SkillWind();
		virtual ~SkillWind();

		virtual void Update()override;
		virtual void Initialize()override;

		virtual void Enter()override;
		virtual void Exit()override;

	private:
		void activeskill_wind();
		void create_wind();

	private:
		bool m_bStart;

		class Wind* m_pWind;
	};
}


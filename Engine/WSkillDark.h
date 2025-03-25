#pragma once
#include "WSkillState.h"

namespace W
{
	class SkillDark : public SkillState
	{
	public:
		SkillDark();
		virtual ~SkillDark();

		virtual void Enter()override;
		virtual void Exit()override;

		virtual void Update()override;
		virtual void Initialize()override;

	private:
	};
}



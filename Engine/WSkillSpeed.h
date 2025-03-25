#pragma once
#include "WSkillState.h"

namespace W
{
	class SkillSpeed : public SkillState
	{
	public:
		SkillSpeed();
		virtual ~SkillSpeed();
		
		virtual void Enter()override;
		virtual void Exit()override;

		virtual void Update()override;
		virtual void Initialize()override;

	private:
		void activeskill_jump();
	};
}



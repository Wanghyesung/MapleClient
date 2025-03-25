#pragma once
#include "WSkillState.h"

namespace W
{
	class SkillJump : public SkillState
	{
	public:
		SkillJump();
		virtual ~SkillJump();

		virtual void Enter()override;
		virtual void Exit()override;

		virtual void Update()override;
		virtual void Initialize()override;

	private:
		void activeskill_jump();

	};
}



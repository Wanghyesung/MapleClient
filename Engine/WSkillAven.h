#pragma once
#include "WSkillState.h"

namespace W
{
	class SkillAven :public SkillState
	{
	public:
		SkillAven();
		virtual ~SkillAven();

		virtual void Update()override;
		virtual void Initialize()override;

		virtual void Enter()override;
		virtual void Exit()override;

	private:
		void activeskill_aven();
		void create_aven();
	private:
		UINT m_iCallStack;
		bool m_bStart;
	};
}


